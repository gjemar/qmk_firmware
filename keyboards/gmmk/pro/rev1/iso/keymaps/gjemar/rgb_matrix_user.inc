// !!! DO NOT ADD #pragma once !!! //
//
// Custom RGB Matrix effect: smooth traveling wave diagonally
// bottom-left -> top-right
//
// Requires: "RGB_MATRIX_CUSTOM_USER = yes" in rules.mk

RGB_MATRIX_EFFECT(neon_sunset)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Speed (1 to 100)
#define NEON_SUNSET_SPEED 10

static bool neon_sunset(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Colors
    const uint8_t rA = 70,  gA =  0,  bA = 190; // purple
    const uint8_t rB = 255, gB = 120, bB =   0; // orange/yellow

    // Global brightness (RM_VALU/RM_VALD)
    const uint8_t val = rgb_matrix_get_val();

    // Calculate speed
    const uint16_t eff = (uint16_t)NEON_SUNSET_SPEED * 200 / 100;
    const uint8_t  time = (eff == 0) ? 0 : (uint8_t)((((uint32_t)g_rgb_timer) * eff) >> 8);

    // Wave tuning
    const uint8_t WAVES = 2;    // 1 = broader/calm, 2-3 = more ripples
    const uint8_t X_MAX = 224;  // GMMK Pro typical X span
    const uint8_t Y_MAX = 64;   // GMMK Pro typical Y span

    // Row thickness
    const uint8_t PAIRS = (MATRIX_ROWS + 1) / 2;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        const uint8_t x = g_led_config.point[i].x;
        const uint8_t y = g_led_config.point[i].y;

        // Normalize x to 0..255
        const uint8_t xn = (uint8_t)(((uint16_t)x * 255) / X_MAX);

        // Estimate matrix row from y, then quantize into 2-row pairs
        uint8_t row = (uint8_t)(((uint16_t)y * MATRIX_ROWS) / (Y_MAX + 1));
        if (row >= MATRIX_ROWS) row = MATRIX_ROWS - 1;

        const uint8_t pair = (uint8_t)(row / 2); // 0..PAIRS-1

        // Map pair index back to 0..255 (pairs form thicker "rows" of color)
        uint8_t ypair_norm = 0;
        if (PAIRS > 1) {
            ypair_norm = (uint8_t)(((uint16_t)pair * 255) / (PAIRS - 1));
        }

        // Diagonal coordinate for bottom-left -> top-right:
        const uint16_t diag16 = (uint16_t)xn + (uint16_t)(255 - ypair_norm);
        const uint8_t  d      = (uint8_t)(diag16 >> 1);

        // Traveling wave along the diagonal (subtract time = movement direction)
        const uint8_t phase = (uint8_t)((uint16_t)d * WAVES - time);

        // Smooth blend factor 0..255
        const uint8_t mix = sin8(phase);

        // Blend A -> B per-LED
        uint8_t r = lerp8by8(rA, rB, mix);
        uint8_t g = lerp8by8(gA, gB, mix);
        uint8_t b = lerp8by8(bA, bB, mix);

        // Apply global brightness
        r = scale8(r, val);
        g = scale8(g, val);
        b = scale8(b, val);

        rgb_matrix_set_color(i, r, g, b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS