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
#define RGB_MODE_WIN      RGB_SUNSET_ORANGE
#define RGB_MODE_MAC      RGB_SUNSET_PURPLE
#define RGB_MODE_GAME1    0,   255, 0
#define RGB_MODE_GAME2    RGB_SIGNAL_RED

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

// Apply code-layer colors with independent background and active-key palettes.
static void set_code_layer_colors(uint8_t layer, uint8_t led_min, uint8_t led_max,
                                  uint8_t base_r, uint8_t base_g, uint8_t base_b,
                                  uint8_t active_r, uint8_t active_g, uint8_t active_b) {
    set_led_range_color(led_min, led_max, base_r, base_g, base_b);
    set_non_transparent_keys_color(layer, active_r, active_g, active_b);
}

// Set one color on all 4 mode-switch keys.
static void set_all_mode_keys_color(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < MODE_KEY_COUNT; i++) {
        set_key_color_from_keypos(MODE_KEYS[i], r, g, b);
    }
}

// _FN layer uses one dedicated color per mode-switch key.
static void set_fn_mode_key_colors(void) {
    set_key_color_from_keypos(MODE_KEYS[MODE_KEY_WIN_IDX], RGB_MODE_WIN);     // KC_PSCR
    set_key_color_from_keypos(MODE_KEYS[MODE_KEY_MAC_IDX], RGB_MODE_MAC);     // KC_PGUP
    set_key_color_from_keypos(MODE_KEYS[MODE_KEY_GAME1_IDX], RGB_MODE_GAME1); // KC_PGDN
    set_key_color_from_keypos(MODE_KEYS[MODE_KEY_GAME2_IDX], RGB_MODE_GAME2); // KC_END
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
        set_code_layer_colors(_WIN_CODE, led_min, led_max, RGB_SUNSET_ORANGE, RGB_SUNSET_PURPLE);
    }

    // _MAC_CODE LAYER
    if (layer == _MAC_CODE) {
        set_code_layer_colors(_MAC_CODE, led_min, led_max, RGB_SUNSET_PURPLE, RGB_SUNSET_ORANGE);
    }

    // KC_PSCR, KC_PGUP, KC_PGDN, KC_END colors by active layer.
    if (layer == _FN) {
        set_fn_mode_key_colors();
    } else if (layer == _GAME1) {
        set_all_mode_keys_color(RGB_MODE_GAME1);
    } else if (layer == _GAME2) {
        set_all_mode_keys_color(RGB_MODE_GAME2);
    } else if (layer == _MAC_BASE || layer == _MAC_CODE) {
        set_all_mode_keys_color(RGB_MODE_MAC);
    } else {
        set_all_mode_keys_color(RGB_MODE_WIN);
    }

    return true;
}
#endif
