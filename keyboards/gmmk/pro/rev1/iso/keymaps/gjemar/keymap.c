#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

// Layer names
enum layer_names {
    _WIN_BASE = 0,
    _WIN_CODE,
    _MAC_BASE,
    _MAC_CODE,
    _GAME1,
    _GAME2,
    _FN,
};

enum custom_keycodes {
    CK_WIN_BASE = SAFE_RANGE,
    CK_MAC_BASE,
    CK_GAME1,
    CK_GAME2,
};

// Sunset RGB colors (match your rgb_matrix_user.inc)
#define RGB_SUNSET_PURPLE 70,  0, 190
#define RGB_SUNSET_ORANGE 255, 120, 0
#define RGB_SIGNAL_RED    255, 0,   0
#define RGB_ACTIVE_LAYER  0,   255, 0

// Mac-specific symbol shortcuts for NO layout on macOS
#define MAC_LBRC LALT(KC_8)
#define MAC_RBRC LALT(KC_9)
#define MAC_LCBR LALT(LSFT(KC_8))
#define MAC_RCBR LALT(LSFT(KC_9))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WIN_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            LT(_WIN_CODE, KC_SPC),                  KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_MAC_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            LT(_MAC_CODE, KC_SPC),                  KC_RGUI, MO(_FN), KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // _GAME1:
    // - Clean gaming layer (no key remaps)
    // - SPACE is forced to normal KC_SPC
    [_GAME1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            KC_SPC,                             _______, _______, _______, _______, _______, _______
    ),

    // _GAME2:
    // - Clean gaming layer (no key remaps)
    // - SPACE is forced to normal KC_SPC
    [_GAME2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            KC_SPC,                             _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          CK_WIN_BASE,
        _______, _______, RM_VALU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   CK_MAC_BASE,
        _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          CK_GAME1,
        _______, _______, _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RM_NEXT, CK_GAME2,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),

    // _WIN_CODE layer:
    // - Activated by holding SPACE on _WIN_BASE (LT(_WIN_CODE, KC_SPC))
    // - LEDs: all keys purple, mapped keys orange/yellow
    //
    // Current mappings:
    //   1 / 2 -> ( )
    //   Q / W -> [ ]
    //   A / S -> { }
    [_WIN_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, NO_LPRN, NO_RPRN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, NO_LBRC, NO_RBRC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, NO_LCBR, NO_RCBR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // _MAC_CODE layer:
    // - Same intent as _WIN_CODE, but mapped for macOS NO layout symbols
    [_MAC_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, NO_LPRN, NO_RPRN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, MAC_LBRC, MAC_RBRC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, MAC_LCBR, MAC_RCBR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_GAME1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_GAME2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_WIN_CODE] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_MAC_CODE] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

static void switch_to_base_layer(uint8_t target_base_layer) {
    layer_off(_GAME1);
    layer_off(_GAME2);
    layer_move(target_base_layer);
}

static void toggle_game_layer(uint8_t target_game_layer) {
    bool already_active = layer_state_cmp(layer_state, target_game_layer);

    layer_off(_GAME1);
    layer_off(_GAME2);

    if (!already_active) {
        layer_on(target_game_layer);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_WIN_BASE:
            if (record->event.pressed) {
                switch_to_base_layer(_WIN_BASE);
            }
            return false;
        case CK_MAC_BASE:
            if (record->event.pressed) {
                switch_to_base_layer(_MAC_BASE);
            }
            return false;
        case CK_GAME1:
            if (record->event.pressed) {
                toggle_game_layer(_GAME1);
            }
            return false;
        case CK_GAME2:
            if (record->event.pressed) {
                toggle_game_layer(_GAME2);
            }
            return false;
    }
    return true;
}

// -------- Effects and animations --------
#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_neon_sunset);
}
#endif

// -------- Layer RGB feedback --------
#ifdef RGB_MATRIX_ENABLE
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

static void set_key_color_from_keypos(keypos_t pos, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t led = g_led_config.matrix_co[pos.row][pos.col];
    if (led == NO_LED) {
        return;
    }

    rgb_matrix_set_color(led, r, g, b);
}

static void set_key_hsv_from_keypos(keypos_t pos, uint8_t h, uint8_t s, uint8_t v) {
    RGB rgb = hsv_to_rgb((HSV){ .h = h, .s = s, .v = v });
    set_key_color_from_keypos(pos, rgb.r, rgb.g, rgb.b);
}

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

static void set_mode_key_wave(void) {
    const keypos_t mode_win   = { .row = 6, .col = 5 }; // PSCR position
    const keypos_t mode_mac   = { .row = 1, .col = 5 }; // PGUP position
    const keypos_t mode_game1 = { .row = 2, .col = 5 }; // PGDN position
    const keypos_t mode_game2 = { .row = 7, .col = 5 }; // END position

    uint8_t hue = (uint8_t)(g_rgb_timer >> 4);
    uint8_t val = rgb_matrix_get_val();

    set_key_hsv_from_keypos(mode_win, hue + 0, 255, val);
    set_key_hsv_from_keypos(mode_mac, hue + 64, 255, val);
    set_key_hsv_from_keypos(mode_game1, hue + 128, 255, val);
    set_key_hsv_from_keypos(mode_game2, hue + 192, 255, val);
}

static keypos_t get_active_mode_switch_keypos(void) {
    const keypos_t mode_win   = { .row = 6, .col = 5 }; // PSCR position
    const keypos_t mode_mac   = { .row = 1, .col = 5 }; // PGUP position
    const keypos_t mode_game1 = { .row = 2, .col = 5 }; // PGDN position
    const keypos_t mode_game2 = { .row = 7, .col = 5 }; // END position

    if (layer_state_cmp(layer_state, _GAME2)) {
        return mode_game2;
    }

    if (layer_state_cmp(layer_state, _GAME1)) {
        return mode_game1;
    }

    if (layer_state_cmp(layer_state, _MAC_BASE) || layer_state_cmp(layer_state, _MAC_CODE)) {
        return mode_mac;
    }

    return mode_win;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    // _FN LAYER
    if (layer == _FN) {
        // 1) Default all LEDs to orange/yellow
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, RGB_SUNSET_ORANGE);
        }

        // 2) Highlight the QK_BOOT key in red
        set_key_color_from_layer_keycode(_FN, QK_BOOT, RGB_SIGNAL_RED);
    }

    // _WIN_CODE LAYER
    if (layer == _WIN_CODE) {
        // 1) Default all LEDs to purple
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, RGB_SUNSET_PURPLE);
        }

        // 2) Highlight keys that are actually mapped on the _WIN_CODE layer
        set_non_transparent_keys_color(_WIN_CODE, RGB_SUNSET_ORANGE);

    }

    // _MAC_CODE LAYER
    if (layer == _MAC_CODE) {
        // 1) Default all LEDs to purple
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, RGB_SUNSET_PURPLE);
        }

        // 2) Highlight keys that are actually mapped on the _MAC_CODE layer
        set_non_transparent_keys_color(_MAC_CODE, RGB_SUNSET_ORANGE);

    }

    // Mode switch keys always run a color wave, then active mode key is forced green.
    set_mode_key_wave();
    set_key_color_from_keypos(get_active_mode_switch_keypos(), RGB_ACTIVE_LAYER);

    return true;
}
#endif
