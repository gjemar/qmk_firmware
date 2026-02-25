#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

// Layer names
enum layer_names {
    _BASE = 0,
    _FN,
    _CODE,
};

// Sunset RGB colors (match your rgb_matrix_user.inc)
#define RGB_SUNSET_PURPLE 70,  0, 190
#define RGB_SUNSET_ORANGE 255, 120, 0
#define RGB_SIGNAL_RED    255, 0,   0

// Wrapper to pass RGB macros into the indicator macro safely
#define INDICATOR_SET(i, ...) RGB_MATRIX_INDICATOR_SET_COLOR((i), __VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            LT(_CODE, KC_SPC),                      KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, RM_VALU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RM_NEXT, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),

    // _CODE layer:
    // - Activated by holding SPACE (LT(_CODE, KC_SPC))
    // - LEDs: all keys purple, mapped keys orange/yellow
    //
    // Current mappings:
    //   1 / 2 -> ( )
    //   Q / W -> [ ]
    //   A / S -> { }
    [_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, NO_LPRN, NO_RPRN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, NO_LBRC, NO_RBRC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, NO_LCBR, NO_RCBR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_CODE] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

// -------- Effects and animations --------
#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_neon_sunset);
}
#endif

// -------- Layer RGB feedback --------
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    // _FN LAYER
    if (layer == _FN) {
        // 1) Default all LEDs to orange/yellow
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, RGB_SUNSET_ORANGE);
        }

        // 2) Highlight the QK_BOOT key in red
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (keymap_key_to_keycode(_FN, (keypos_t){ .row = row, .col = col }) != QK_BOOT) {
                    continue;
                }

                uint8_t led = g_led_config.matrix_co[row][col];
                if (led == NO_LED) {
                    continue;
                }

                INDICATOR_SET(led, RGB_SIGNAL_RED);
            }
        }
    }

    // _CODE LAYER
    if (layer == _CODE) {
        // 1) Default all LEDs to purple
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, RGB_SUNSET_PURPLE);
        }

        // 2) Highlight keys that are actually mapped on the _CODE layer (non-transparent)
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint16_t kc = keymap_key_to_keycode(_CODE, (keypos_t){ .row = row, .col = col });
                if (kc == KC_TRNS) {
                    continue;
                }

                uint8_t led = g_led_config.matrix_co[row][col];
                if (led == NO_LED) {
                    continue;
                }

                // Orange/yellow for mapped keys
                INDICATOR_SET(led, RGB_SUNSET_ORANGE);
            }
        }
    }

    return true;
}
#endif