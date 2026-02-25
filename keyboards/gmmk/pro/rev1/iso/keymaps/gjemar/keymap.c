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

// Custom keycodes for mode switching.
enum custom_keycodes {
    CK_WIN_BASE = SAFE_RANGE,
    CK_MAC_BASE,
    CK_GAME1,
    CK_GAME2,
};

// Mac-specific symbol shortcuts for NO layout on macOS
#define MAC_LBRC LALT(KC_8)
#define MAC_RBRC LALT(KC_9)
#define MAC_LCBR LALT(LSFT(KC_8))
#define MAC_RCBR LALT(LSFT(KC_9))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Base layer for windows
    [_WIN_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            LT(_WIN_CODE, KC_SPC),                  KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Base layer for mac
    [_MAC_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            LT(_MAC_CODE, KC_SPC),                  KC_RGUI, MO(_FN), KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Layout 1 for gaming
    [_GAME1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            KC_SPC,                             _______, _______, _______, _______, _______, _______
    ),

    // Layout 2 for gaming
    [_GAME2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            KC_SPC,                             _______, _______, _______, _______, _______, _______
    ),

    // Function layout (hold FN for activation)
    [_FN] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          CK_WIN_BASE,
        _______, _______, RM_VALU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   CK_MAC_BASE,
        _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          CK_GAME1,
        _______, _______, _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RM_NEXT, CK_GAME2,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),

    // Code layer for windows (hold space for activation)
    [_WIN_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, NO_LPRN, NO_RPRN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, NO_LBRC, NO_RBRC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, NO_LCBR, NO_RCBR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // Code layer for mac (hold space for activation)
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
#include "rgb_layer_indicators.inc"
