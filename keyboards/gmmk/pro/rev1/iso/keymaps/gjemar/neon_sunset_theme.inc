// !!! DO NOT ADD #pragma once !!! //
//
// Neon Sunset custom RGB matrix effect.
// Smooth diagonal wave from bottom-left to top-right.
//
// Requires: "RGB_MATRIX_CUSTOM_USER = yes" in rules.mk

RGB_MATRIX_EFFECT(neon_sunset)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Effect tuning
#define NEON_SUNSET_SPEED 10   // 1..100
#define NEON_SUNSET_WAVES 2    // 1 = broad, 2..3 = more ripples
#define NEON_SUNSET_X_MAX 224  // GMMK Pro typical X span
#define NEON_SUNSET_Y_MAX 64   // GMMK Pro typical Y span

// Palette (A -> B)
#define NEON_SUNSET_A_R 70
#define NEON_SUNSET_A_G 0
#define NEON_SUNSET_A_B 190
#define NEON_SUNSET_B_R 255
#define NEON_SUNSET_B_G 120
#define NEON_SUNSET_B_B 0

static bool neon_sunset(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Global brightness (RM_VALU/RM_VALD)
    const uint8_t brightness = rgb_matrix_get_val();

    // Effect speed scaling from QMK's timer domain
    const uint16_t speed = (uint16_t)NEON_SUNSET_SPEED * 200 / 100;
    const uint8_t  time  = (speed == 0) ? 0 : (uint8_t)((((uint32_t)g_rgb_timer) * speed) >> 8);

    // Pair rows for thicker horizontal color bands.
    const uint8_t pair_count = (MATRIX_ROWS + 1) / 2;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        const uint8_t x = g_led_config.point[i].x;
        const uint8_t y = g_led_config.point[i].y;

        // Normalize x to 0..255
        const uint8_t x_norm = (uint8_t)(((uint16_t)x * 255) / NEON_SUNSET_X_MAX);

        // Estimate matrix row from y, then quantize into 2-row pairs.
        uint8_t row = (uint8_t)(((uint16_t)y * MATRIX_ROWS) / (NEON_SUNSET_Y_MAX + 1));
        if (row >= MATRIX_ROWS) {
            row = MATRIX_ROWS - 1;
        }

        const uint8_t pair = (uint8_t)(row / 2); // 0..pair_count-1

        // Map pair index back to 0..255 (thicker "rows" of color).
        uint8_t pair_norm = 0;
        if (pair_count > 1) {
            pair_norm = (uint8_t)(((uint16_t)pair * 255) / (pair_count - 1));
        }

        // Diagonal coordinate for bottom-left -> top-right.
        const uint16_t diag16 = (uint16_t)x_norm + (uint16_t)(255 - pair_norm);
        const uint8_t  diag   = (uint8_t)(diag16 >> 1);

        // Traveling wave along the diagonal.
        const uint8_t phase = (uint8_t)((uint16_t)diag * NEON_SUNSET_WAVES - time);

        // Smooth blend A -> B
        const uint8_t mix = sin8(phase);
        uint8_t r = lerp8by8(NEON_SUNSET_A_R, NEON_SUNSET_B_R, mix);
        uint8_t g = lerp8by8(NEON_SUNSET_A_G, NEON_SUNSET_B_G, mix);
        uint8_t b = lerp8by8(NEON_SUNSET_A_B, NEON_SUNSET_B_B, mix);

        // Apply global brightness
        r = scale8(r, brightness);
        g = scale8(g, brightness);
        b = scale8(b, brightness);

        rgb_matrix_set_color(i, r, g, b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
