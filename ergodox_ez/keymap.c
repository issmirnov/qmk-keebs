#include QMK_KEYBOARD_H
#include "version.h"

enum ergodox_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define CTL_SPC MT(MOD_LCTL, KC_SPC)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define LOW(key) LT(_LOWER, KC_##key)
#define RAI(key) LT(_RAISE, KC_##key)

#define LOCK_SCR LCA(KC_L)
#define TERMINAL LCA(KC_T)

#define BR_BACK LALT(KC_LEFT)
#define BR_FWD LALT(KC_RIGHT)

#define WKSP_LFT LGUI(KC_LEFT)
#define WKSP_RGT LGUI(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ergodox(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F5,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
  KC_LSFT, LOW(Z),  RAI(X),  KC_C,    KC_V,    KC_B,    _______,
  _______, KC_LCTL, KC_LGUI, KC_LALT, LOWER,
                                               KC_DEL,  KC_MPLY,
                                                        KC_HOME,
                                      CTL_SPC, KC_BSPC, KC_END,

  RESET,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  LOW(SLSH), KC_RSFT,
                    RAISE,   KC_DOWN, KC_UP,   KC_LEFT, KC_RGHT,
  LOCK_SCR, TERMINAL,
  KC_PGUP,
  KC_PGDN, KC_ENT,  KC_SPC
),

[_LOWER] = LAYOUT_ergodox(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_LCBR, KC_RCBR, _______,
  _______, KC_PERC, KC_CIRC, KC_DLR,  KC_LPRN, KC_RPRN,
  _______, _______, _______, KC_TILD, KC_LBRC, KC_RBRC, _______,
  _______, _______, _______, _______, _______,
                                               _______, _______,
                                                        _______,
                                      _______, _______, _______,

  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_BSLS, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,  _______,
           KC_PIPE, KC_UNDS, KC_MINS, KC_QUOT, KC_DQT,  _______,
  _______, XXXXXXX, KC_GRV,  KC_LT,   KC_GT,   _______, _______,
                    _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END,
  _______, _______,
  _______,
  _______, _______, _______
),

[_RAISE] = LAYOUT_ergodox(
  _______, _______, _______, _______, _______, _______, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,
  _______, _______, _______, _______, BR_BACK, BR_FWD,
  _______, _______, _______, _______, WKSP_LFT,WKSP_RGT,_______,
  _______, _______, _______, _______, _______,
                                               KC_MPRV, KC_MNXT,
                                                        KC_VOLU,
                                      _______, _______, KC_VOLD,

  _______, _______, _______, _______, _______, _______, _______,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
           _______, KC_4,    KC_5,    KC_6,    _______, _______,
  _______, _______, KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                    _______, _______, _______, _______, _______,
  _______, _______,
  _______,
  _______, _______, _______
),

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case _LOWER:
        ergodox_right_led_1_on();
        break;
      case _RAISE:
        ergodox_right_led_2_on();
        break;
      default:
        break;
    }

  return state;
};
