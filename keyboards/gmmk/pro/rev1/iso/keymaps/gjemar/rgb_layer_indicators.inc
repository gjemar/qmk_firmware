#ifdef RGB_MATRIX_ENABLE
enum { MODE_KEY_COUNT = 4 };
enum mode_key_index {
    MODE_KEY_WIN_IDX = 0,
    MODE_KEY_MAC_IDX,
    MODE_KEY_GAME1_IDX,
    MODE_KEY_GAME2_IDX,
};

static const keypos_t MODE_KEYS[MODE_KEY_COUNT] = {
    { .row = 6, .col = 5 }, // WIN
    { .row = 1, .col = 5 }, // MAC
    { .row = 2, .col = 5 }, // GAME1
    { .row = 7, .col = 5 }, // GAME2
};

// Sunset RGB colors (match neon_sunset_theme.inc)
#define RGB_SUNSET_PURPLE 70,  0, 190
#define RGB_SUNSET_ORANGE 255, 120, 0
#define RGB_SIGNAL_RED    255, 0,   0
#define RGB_ACTIVE_LAYER  0,   255, 0

static const uint8_t MODE_WAVE_OFFSETS[MODE_KEY_COUNT] = { 0, 64, 128, 192 };

// Enable RGB and select the custom default effect on boot.
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_neon_sunset);
}

// Set color for all keys on a layer matching a specific keycode.
static void set_key_color_from_layer_keycode(uint8_t layer, uint16_t keycode, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (keymap_key_to_keycode(layer, (keypos_t){ .row = row, .col = col }) != keycode) {
                continue;
            }

            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED) {
                continue;
            }

            rgb_matrix_set_color(led, r, g, b);
        }
    }
}

// Set color for a single key by matrix position.
static void set_key_color_from_keypos(keypos_t pos, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t led = g_led_config.matrix_co[pos.row][pos.col];
    if (led == NO_LED) {
        return;
    }

    rgb_matrix_set_color(led, r, g, b);
}

// Convert HSV to RGB and apply to a single key position.
static void set_key_hsv_from_keypos(keypos_t pos, uint8_t h, uint8_t s, uint8_t v) {
    RGB rgb = hsv_to_rgb((HSV){ .h = h, .s = s, .v = v });
    set_key_color_from_keypos(pos, rgb.r, rgb.g, rgb.b);
}

// Color all non-transparent keys defined on a layer.
static void set_non_transparent_keys_color(uint8_t layer, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){ .row = row, .col = col });
            if (kc == KC_TRNS) {
                continue;
            }

            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED) {
                continue;
            }

            rgb_matrix_set_color(led, r, g, b);
        }
    }
}

// Fill an LED index range with one RGB color.
static void set_led_range_color(uint8_t led_min, uint8_t led_max, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
}

// Apply the standard code-layer palette (purple base, orange mapped keys).
static void set_code_layer_colors(uint8_t layer, uint8_t led_min, uint8_t led_max) {
    set_led_range_color(led_min, led_max, RGB_SUNSET_PURPLE);
    set_non_transparent_keys_color(layer, RGB_SUNSET_ORANGE);
}

// Animate rainbow wave colors on the mode-switch keys.
static void set_mode_key_wave(void) {
    uint8_t hue = (uint8_t)(g_rgb_timer >> 4);
    uint8_t val = rgb_matrix_get_val();

    for (uint8_t i = 0; i < MODE_KEY_COUNT; i++) {
        set_key_hsv_from_keypos(MODE_KEYS[i], hue + MODE_WAVE_OFFSETS[i], 255, val);
    }
}

// Return the mode key position that represents the active mode.
static keypos_t get_active_mode_switch_keypos(void) {
    if (layer_state_cmp(layer_state, _GAME2)) {
        return MODE_KEYS[MODE_KEY_GAME2_IDX];
    }

    if (layer_state_cmp(layer_state, _GAME1)) {
        return MODE_KEYS[MODE_KEY_GAME1_IDX];
    }

    if (layer_state_cmp(layer_state, _MAC_BASE) || layer_state_cmp(layer_state, _MAC_CODE)) {
        return MODE_KEYS[MODE_KEY_MAC_IDX];
    }

    return MODE_KEYS[MODE_KEY_WIN_IDX];
}

// Apply per-layer indicator colors on top of the base RGB effect.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    // _FN LAYER
    if (layer == _FN) {
        // 1) Default all LEDs to orange/yellow
        set_led_range_color(led_min, led_max, RGB_SUNSET_ORANGE);

        // 2) Highlight the QK_BOOT key in red
        set_key_color_from_layer_keycode(_FN, QK_BOOT, RGB_SIGNAL_RED);
    }

    // _WIN_CODE LAYER
    if (layer == _WIN_CODE) {
        set_code_layer_colors(_WIN_CODE, led_min, led_max);
    }

    // _MAC_CODE LAYER
    if (layer == _MAC_CODE) {
        set_code_layer_colors(_MAC_CODE, led_min, led_max);
    }

    // Mode switch keys always run a color wave, then active mode key is forced green.
    set_mode_key_wave();
    set_key_color_from_keypos(get_active_mode_switch_keypos(), RGB_ACTIVE_LAYER);

    return true;
}
#endif
