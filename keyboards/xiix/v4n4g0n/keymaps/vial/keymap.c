#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,
        KC_ESC,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
        KC_TAB,    KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_ENT,
        KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_UP,     KC_RSFT,              
        KC_LCTL,   KC_LGUI,   KC_LALT,                         KC_SPC,                                     KC_LEFT,   KC_DOWN,   KC_RGHT
    )
};

/* aRGB Configuration */
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {           NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  {      2,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  {      1,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  {      0,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  { NO_LED,   NO_LED,   NO_LED,                       NO_LED,                                 NO_LED,   NO_LED,   NO_LED }
}, {
  // LED Index to Physical Position
  { 0,  16 }, { 0,  8 }, { 0,  5 }
}, {
  // LED Index to Flag
  8, 8, 8
} };

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_SET_COLOR(0, 0, 255, 0); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_SET_COLOR(0, 0, 0, 0);
    }
    return true;
}