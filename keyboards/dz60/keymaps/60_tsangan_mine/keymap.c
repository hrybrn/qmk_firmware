#include QMK_KEYBOARD_H

enum custom_keycodes {
  // macros
  BACK_TAB = SAFE_RANGE,
  FORWARD_TAB,
  CLOSE_TAB_WIN,
  CLOSE_TAB_MAC,
  SEARCH_MAC,
  SEARCH_WIN
};

// macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACK_TAB:
      if (record->event.pressed) SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_TAB)))); break;
    case FORWARD_TAB:
      if (record->event.pressed) SEND_STRING(SS_LCTRL(SS_TAP(X_TAB))); break;
    case CLOSE_TAB_WIN:
      if (record->event.pressed) SEND_STRING(SS_LCTRL("w")); break;
    case CLOSE_TAB_MAC:
      if (record->event.pressed) SEND_STRING(SS_LGUI("w")); break;
    case SEARCH_MAC:
      if (record->event.pressed) SEND_STRING(SS_LGUI("ctv") SS_TAP(X_ENTER)); break;
    case SEARCH_WIN:
      if (record->event.pressed) SEND_STRING(SS_LCTRL("ctv") SS_TAP(X_ENTER)); break;
  }
  return true;
}

// tap dance
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  CAPS_SPECIAL = 0,
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void tap_dance_caps (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: SEND_STRING(SS_TAP(X_F19)); break;
    case DOUBLE_TAP: SEND_STRING("();" SS_TAP(X_ENTER)); break;
    case TRIPLE_TAP: reset_keyboard(); break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CAPS_SPECIAL] = ACTION_TAP_DANCE_FN(tap_dance_caps)
};

// keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_60_tsangan(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, TD(CAPS_SPECIAL), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP), LT(1,KC_NO), KC_LCTRL, KC_LALT, KC_LGUI, KC_SPC, RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_RGHT)),
	[1] = LAYOUT_60_tsangan(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, KC_UP, KC_NO, KC_NO, TO(3), KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_HOME, KC_LEFT, KC_RGHT, KC_NO, MAGIC_SWAP_ALT_GUI, BACK_TAB, FORWARD_TAB, CLOSE_TAB_MAC, SEARCH_MAC, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_END, KC_DOWN, LT(2,KC_NO), KC_NO, MAGIC_UNSWAP_ALT_GUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[2] = LAYOUT_60_tsangan(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT_60_tsangan(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, LT(4,KC_NO), KC_LCTRL, KC_NO, KC_LALT, KC_SPC, KC_NO, KC_RALT, KC_RCTL),
	[4] = LAYOUT_60_tsangan(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, KC_UP, KC_NO, KC_NO, TO(0), KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_HOME, KC_LEFT, KC_RGHT, KC_NO, KC_NO, BACK_TAB, FORWARD_TAB, CLOSE_TAB_WIN, SEARCH_WIN, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_END, KC_DOWN, LT(2,KC_NO), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

