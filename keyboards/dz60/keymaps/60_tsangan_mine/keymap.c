#include QMK_KEYBOARD_H

// macro keycodes
enum custom_keycodes {
  BACK_TAB = SAFE_RANGE,
  FORWARD_TAB,
  CLOSE_TAB,
  SEARCH,
  LGUI_SWITCH,
  LALT_SWITCH,
  WINDOWS_MODE_TOGGLE,
  COPYPASTA_HELI,
  COPYPASTA_CHEAT,
  COPYPASTA_GREEK_SALT,
  COPYPASTA_DARTH_PLAGUEIS,
  DEFAULT_QBO_PASSWORD,
  OPEN_PAGE_IN_NEW_INCOGNITO,
  US_PHONE_NUMBER
};

bool windows_mode = false;

// macro functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACK_TAB:
      if (record->event.pressed) SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_TAB)))); break;
    case FORWARD_TAB:
      if (record->event.pressed) SEND_STRING(SS_LCTRL(SS_TAP(X_TAB))); break;
    case WINDOWS_MODE_TOGGLE:
      if (record->event.pressed) {
        windows_mode = !windows_mode;
      }
      break;
    case COPYPASTA_HELI:
      if (record->event.pressed) SEND_STRING("I sexually Identify as an Attack Helicopter. Ever since I was a boy I dreamed of soaring over the oilfields dropping hot sticky loads on disgusting foreigners. People say to me that a person being a helicopter is Impossible and I’m fucking retarded but I don’t care, I’m beautiful. I’m having a plastic surgeon install rotary blades, 30 mm cannons and AMG-114 Hellfire missiles on my body. From now on I want you guys to call me “Apache” and respect my right to kill from above and kill needlessly. If you can’t accept me you’re a heliphobe and need to check your vehicle privilege. Thank you for being so understanding."); break;
    case COPYPASTA_CHEAT:
      if (record->event.pressed) SEND_STRING("You cheated not only the game, but yourself. You didn't grow. You didn't improve. You took a shortcut and gained nothing. You experienced a hollow victory. Nothing was risked and nothing was gained. It's sad that you don't know the difference."); break;
    case COPYPASTA_GREEK_SALT:
      if (record->event.pressed) SEND_STRING("High in orbit, the Gitraktmaet motherships descend upon the Earth. They prepare to enslave the world and mine it for all its salt, but the scanners detect an abnormally high concentration inside a tiny shack in Greece. The invasion won't be necessary. \"Lock onto him with the RNG disruptor,\" says the captain, greedily. \"Soon we shall have all the salt we need.\""); break;
    case COPYPASTA_DARTH_PLAGUEIS:
      if (record->event.pressed) SEND_STRING("Did you ever hear the tragedy of Darth Plagueis The Wise? I thought not. It’s not a story the Jedi would tell you. It’s a Sith legend. Darth Plagueis was a Dark Lord of the Sith, so powerful and so wise he could use the Force to influence the midichlorians to create life… He had such a knowledge of the dark side that he could even keep the ones he cared about from dying. The dark side of the Force is a pathway to many abilities some consider to be unnatural. He became so powerful… the only thing he was afraid of was losing his power, which eventually, of course, he did. Unfortunately, he taught his apprentice everything he knew, then his apprentice killed him in his sleep. Ironic. He could save others from death, but not himself."); break;
    case DEFAULT_QBO_PASSWORD:
      if (record->event.pressed) SEND_STRING("Password1!"); break;
    case US_PHONE_NUMBER:
      if (record->event.pressed) SEND_STRING("5555555555");
  }

  if (windows_mode) {
    switch (keycode) {
      case CLOSE_TAB:
        if (record->event.pressed) SEND_STRING(SS_LCTRL("w")); break;
      case SEARCH:
        if (record->event.pressed) SEND_STRING(SS_LCTRL("ctv") SS_TAP(X_ENTER)); break;
      case LGUI_SWITCH:
        if (record->event.pressed) register_code(KC_LALT);
        else unregister_code(KC_LALT);
        break;
      case LALT_SWITCH:
        if (record->event.pressed) register_code(KC_LGUI);
        else unregister_code(KC_LGUI);
        break;
      case OPEN_PAGE_IN_NEW_INCOGNITO:
        if (record->event.pressed) SEND_STRING(SS_LCTRL("lcw" SS_LSFT("n") "v") SS_TAP(X_ENTER)); break;
    }
  } else {
    switch (keycode) {
      case CLOSE_TAB:
        if (record->event.pressed) SEND_STRING(SS_LGUI("w")); break;
      case SEARCH:
        if (record->event.pressed) SEND_STRING(SS_LGUI("ctv") SS_TAP(X_ENTER)); break;
      case LALT_SWITCH:
        if (record->event.pressed) register_code(KC_LALT);
        else unregister_code(KC_LALT);
        break;
      case LGUI_SWITCH:
        if (record->event.pressed) register_code(KC_LGUI);
        else unregister_code(KC_LGUI);
        break;
      case OPEN_PAGE_IN_NEW_INCOGNITO:
        if (record->event.pressed) {
          SEND_STRING(SS_LGUI("lcw"));
          _delay_ms(25);
          SEND_STRING(SS_LGUI(SS_LSFT("n") "v") SS_TAP(X_ENTER));
        }
        break;
    }
  }
  return true;
}

// generic tap dance setup
enum {
  SINGLE_TAP = 0,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP,
  TRIPLE_HOLD
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

// tap dance keycodes
enum {
  CAPS_SPECIAL = 0
};

// tap dance functions
void tap_dance_caps (qk_tap_dance_state_t *state, void *user_data) {
  switch (cur_dance(state)) {
    case SINGLE_TAP: SEND_STRING(SS_TAP(X_F19)); break;
    case DOUBLE_TAP: SEND_STRING("();" SS_TAP(X_ENTER)); break;
    case TRIPLE_TAP: reset_keyboard(); break;
  }
}

// tap dance setup
qk_tap_dance_action_t tap_dance_actions[] = {
  [CAPS_SPECIAL] = ACTION_TAP_DANCE_FN(tap_dance_caps)
};

// keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_60_tsangan(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, TD(CAPS_SPECIAL), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP), LT(1,KC_NO), KC_LCTRL, LALT_SWITCH, LGUI_SWITCH, KC_SPC, RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_RGHT)),
	[1] = LAYOUT_60_tsangan(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, KC_UP, KC_NO, KC_NO, TO(3), KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_HOME, KC_LEFT, KC_RGHT, KC_NO, WINDOWS_MODE_TOGGLE, BACK_TAB, FORWARD_TAB, CLOSE_TAB, SEARCH, OPEN_PAGE_IN_NEW_INCOGNITO, KC_NO, KC_NO, KC_PGDN, KC_END, KC_DOWN, LT(2,KC_NO), KC_NO, MAGIC_UNSWAP_ALT_GUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[2] = LAYOUT_60_tsangan(KC_NO, COPYPASTA_HELI, COPYPASTA_CHEAT, COPYPASTA_GREEK_SALT, COPYPASTA_DARTH_PLAGUEIS, DEFAULT_QBO_PASSWORD, US_PHONE_NUMBER, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT_60_tsangan(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, LT(4,KC_NO), KC_LCTRL, KC_NO, KC_LALT, KC_SPC, KC_NO, KC_RALT, KC_RCTL),
	[4] = LAYOUT_60_tsangan(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, KC_UP, KC_NO, KC_NO, TO(0), KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_HOME, KC_LEFT, KC_RGHT, KC_NO, KC_NO, KC_NO ,KC_NO ,KC_NO ,KC_NO, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_END, KC_DOWN, LT(2,KC_NO), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

