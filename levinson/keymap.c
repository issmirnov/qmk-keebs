#include "tap_tog.h"

#ifdef AUDIO_ENABLE
  #include "audio.h"
  #include "sounds.h"
#endif


#ifdef RGBLIGHT_ENABLE
  #include "rgb.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Run `./qmk show levinson` from parent dir to see this layer.
// BEAKL
[_BEAKL] = LAYOUT_ortho_4x12_wrapper(
KC_ESC       , KC_Q          , KC_H    , KC_O    , KC_U      , KC_X      , KC_G   , KC_C      , KC_R       , KC_F    , KC_Z    , KC_DEL       ,
KC_TAB       , KC_Y          , KC_I    , KC_E    , KC_A      , KC_DOT    , KC_D   , KC_S      , KC_T       , KC_N    , KC_B    , KC_BSPC      ,
TT(_SHIFTED) , KC_J          , KC_SLSH , KC_COMM , KC_K      , TT(_NUMP) , KC_W   , KC_M      , KC_L       , KC_P    , KC_V    , TT(_SHIFTED) ,

KC_LCTL      , LSFT(KC_LGUI) , KC_LALT , KC_LGUI , TT(_NAVI) , KC_SPC    , KC_ENT , TT(_SYMB) , TT(_MOUSE) , XXXXXXX , XXXXXXX , KC_LCTL
), // Note: visualizer expects this closing parens to be right at the start of the line.

// Run `./qmk show levinson` from parent dir to see this layer.
// Symbols
[_SYMB] = LAYOUT_ortho_4x12_wrapper(
XXXXXXX , XXXXXXX , KC_LT   , KC_AT   , KC_GT   , KC_MINS , KC_QUOT , KC_LBRC , KC_MINS , KC_RBRC , XXXXXXX , XXXXXXX ,
XXXXXXX , KC_SLSH , KC_LPRN , KC_DQT  , KC_RPRN , KC_HASH , KC_PERC , KC_LCBR , KC_EQL  , KC_RCBR , KC_PIPE , XXXXXXX ,
XXXXXXX , KC_DLR  , KC_COLN , KC_ASTR , KC_PLUS , XXXXXXX , XXXXXXX , KC_AMPR , KC_CIRC , KC_TILD , KC_SCLN , XXXXXXX ,
_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
), // Note: visualizer expects this closing parens to be right at the start of the line.

// Run `./qmk show levinson` from parent dir to see this layer.
[_NUMP] = LAYOUT_ortho_4x12_wrapper(
XXXXXXX , XXXXXXX , XXXXXXX , KC_ASTR , KC_EQL  , XXXXXXX , XXXXXXX , KC_3    , KC_2    , KC_5    , XXXXXXX , XXXXXXX ,
XXXXXXX , KC_COLN , KC_SLSH , KC_COMM , KC_DOT  , KC_MINS , KC_4    , KC_0    , KC_1    , KC_DOT  , KC_7    , XXXXXXX ,
XXXXXXX , XXXXXXX , XXXXXXX , KC_PLUS , KC_PERC , _______ , XXXXXXX , KC_8    , KC_9    , KC_6    , XXXXXXX , XXXXXXX ,
XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
), // Note: visualizer expects this closing parens to be right at the start of the line.

// Run `./qmk show levinson` from parent dir to see this layer.
/* [_OVERWATCH] = LAYOUT_ortho_4x12_wrapper( */
/* ______________OVERWATCH_L1_________________ , TO(0)           , XXXXXXX          , XXXXXXX          , XXXXXXX        , XXXXXXX        , EEP_RST , */
/* ______________OVERWATCH_L2_________________ , RGB_MODE_FORWARD, RGB_MODE_REVERSE , XXXXXXX          , XXXXXXX        , XXXXXXX        , RGB_TOG , */
/* ______________OVERWATCH_L3_________________ , RGB_MODE_PLAIN  , RGB_MODE_BREATHE , RGB_MODE_RAINBOW , RGB_MODE_SWIRL , RGB_MODE_SNAKE , XXXXXXX , */
/* ______________OVERWATCH_L4_________________ , KC_SPACE         , XXXXXXX          , XXXXXXX          , XXXXXXX        , XXXXXXX        , XXXXXXX, RGB_MODE_GRADIENT */
/* ), // Note: visualizer expects this closing parens to be right at the start of the line. */

// Run `./qmk show levinson` from parent dir to see this layer.
[_NAVI] = LAYOUT_ortho_4x12_wrapper(
RESET   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_HOME , KC_UP   , KC_END  , XXXXXXX      , XXXXXXX ,
XXXXXXX , KC_LALT,  KC_LCTL , KC_LSFT , KC_LGUI , XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , LGUI(KC_SPC) , XXXXXXX ,
XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PGUP , XXXXXXX , KC_PGDN , XXXXXXX      , XXXXXXX ,
XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ , _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX      , XXXXXXX
), // Note: visualizer expects this closing parens to be right at the start of the line.

// shifted
[_SHIFTED] = LAYOUT_ortho_4x12_wrapper(
_______ , LSFT(KC_Q) , LSFT(KC_H) , LSFT(KC_O) , LSFT(KC_U) , LSFT(KC_X) , LSFT(KC_G) , LSFT(KC_C) , LSFT(KC_R) , LSFT(KC_F) , LSFT(KC_Z) , _______ ,
_______ , LSFT(KC_Y) , LSFT(KC_I) , LSFT(KC_E) , LSFT(KC_A) , KC_GRV     , LSFT(KC_D) , LSFT(KC_S) , LSFT(KC_T) , LSFT(KC_N) , LSFT(KC_B) , _______ ,
_______ , LSFT(KC_J) , KC_QUES    , KC_EXLM    , LSFT(KC_K) , _______    , LSFT(KC_W) , LSFT(KC_M) , LSFT(KC_L) , LSFT(KC_P) , LSFT(KC_V) , _______ ,
_______ , _______    , _______    , _______    , _______    , _______    , _______    , _______    , _______    , _______    , _______    , _______
),

[_MOUSE] = LAYOUT_ortho_4x12_wrapper(
XXXXXXX , XXXXXXX , XXXXXXX   , KC_MS_U , XXXXXXX   , XXXXXXX   , XXXXXXX , KC_WH_U , KC_WH_D , XXXXXXX   , XXXXXXX   , XXXXXXX ,
XXXXXXX , XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_R , XXXXXXX   , XXXXXXX , KC_BTN1 , KC_BTN2 , KC_BTN3 , KC_BTN4 , XXXXXXX ,
XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX , KC_WH_L , KC_WH_R , XXXXXXX   , XXXXXXX   , XXXXXXX ,
XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX   , KC_ACL1 , KC_ACL0 , XXXXXXX , XXXXXXX   , _______ , XXXXXXX   , XXXXXXX   , XXXXXXX
),
// mouse - inverted, incomplete
// decided against this, since right hand is mouse hand.
/* [_MOUSE] = LAYOUT_ortho_4x12_wrapper( */
/* XXXXXXX , KC_WH_U , KC_WH_D , XXXXXXX   , XXXXXXX   , XXXXXXX   , */
/* XXXXXXX , XXXXXXX   , XXXXXXX   , KC_MS_U , XXXXXXX   , XXXXXXX   , */

/* XXXXXXX , KC_BTN4 , KC_BTN3 , KC_BTN2 , KC_BTN1 , XXXXXXX   , */
/* XXXXXXX   , KC_MS_L , KC_MS_D , KC_MS_R , XXXXXXX,  XXXXXXX   , */


/* XXXXXXX , XXXXXXX, XXXXXXX,  KC_WH_L , KC_WH_R     , XXXXXXX   , */
/* XXXXXXX , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , */

/* XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX   , XXXXXXX, */

/* KC_ACL0 , KC_ACL1   , _______   , XXXXXXX   , XXXXXXX, XXXXXXX */
/* ), */

};

// called by QMK during key processing before the actual key event is handled. Useful for macros.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOCK:
      if (record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
#endif
      }
      return true; // Let QMK send the press/release events
      break;

    case TAP_TOG_LAYER:
      process_tap_tog(_SYMB,record);
      return false;
      break;
    default:
      tap_tog_count = 0; // reset counter.
      tap_tog_layer_other_key_pressed = true; // always set this to true, TAP_TOG_LAYER handlers will handle interpreting this
      break;
  }
  return true;
}


// Runs constantly in the background, in a loop every 100ms or so.
// Best used for LED status output triggered when user isn't actively typing.
void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE
    matrix_scan_rgb();
  #endif // RGBLIGHT_ENABLE
}

// only runs when when the layer is changed, good for updating LED's and clearing sticky state
// RGB modes: https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight.h
uint32_t layer_state_set_user(uint32_t state) {
  #ifdef RGBLIGHT_ENABLE
    layer_state_set_rgb(state);
  #endif
  uint8_t layer = biton32(state);
  combo_enable(); // by default, enable combos.
  switch (layer) {
    case 0:
      break;
    case 1:
      clear_mods();
      break;
    case 2:
      clear_mods();
      break;
    case _OVERWATCH:
      clear_mods();
      combo_disable(); // We don't want combos in overwatch
      #ifdef AUDIO_ENABLE
        // PLAY_SONG(song_overwatch);
      #endif
      break;
    default:
      break;
  }
  return state;
};

// Runs boot tasks for keyboard.
// Plays a welcome song and clears RGB state.
void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    keyboard_post_init_rgb();
  #endif
}
