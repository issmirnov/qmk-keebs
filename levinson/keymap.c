#include QMK_KEYBOARD_H

#include "issmirnov.h"
#include "quantum_keycodes.h"

#include "tap_tog.h"

#ifdef AUDIO_ENABLE
  #include "audio.h"
  #include "sounds.h"
#endif


#ifdef RGBLIGHT_ENABLE
  #include "rgb.h"
#endif

extern keymap_config_t keymap_config;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Run `./qmk show levinson` from parent dir to see this layer.
[_QWERTY] = LAYOUT_ortho_4x12_wrapper(
KC_ESC  , _________________QWERTY_L1_________________, _________________QWERTY_R1_________________ , APPS      ,
KC_TAB  , _________________QWERTY_L2_________________, _________________QWERTY_R2_________________ , MO(_NAVI) ,
OSMSFT  , _________________QWERTY_L3_________________, _________________QWERTY_R3_________________ , KC_QUOTE  ,
KC_LCTL , MODSFT , KC_LALT , KC_LGUI , KC_BSPACE , KC_SPC , KC_ENTER , KC_TAB , KC_UP  , KC_DOWN , KC_LEFT       , KC_RGHT
), // Note: visualizer expects this closing parens to be right at the start of the line.

// Run `./qmk show levinson` from parent dir to see this layer.
[_SYMB] = LAYOUT_ortho_4x12_wrapper(
_______ , _________________SYMB_L1___________________, _________________SYMB_R1___________________ , KC_ESC   ,
_______ , _________________SYMB_L2___________________, _________________SYMB_R2___________________ , KC_DQT   ,
_______ , _________________SYMB_L3___________________, _________________SYMB_R3___________________ , KC_QUOTE ,
_______ , ___________________BLANK___________________, _______ , _______ , KC_ESC   , KC_COLN   , KC_PERC       , LOCK
), // Note: visualizer expects this closing parens to be right at the start of the line.

// Run `./qmk show levinson` from parent dir to see this layer.
[_NUMP] = LAYOUT_ortho_4x12_wrapper(
_______ , _________________NUMP_L1___________________ , _________________NUMP_R1___________________ , RESET   ,
_______ , _________________NUMP_L2___________________ , _________________NUMP_R2___________________ , _______ ,
_______ , _________________NUMP_L3___________________ , _________________NUMP_R3___________________ , _______ ,
_______ , ___________________BLANK___________________ , _______ , _______ , _______ , _______ , TO(_OVERWATCH) , _______
), // Note: visualizer expects this closing parens to be right at the start of the line.

// Run `./qmk show levinson` from parent dir to see this layer.
[_OVERWATCH] = LAYOUT_ortho_4x12_wrapper(
______________OVERWATCH_L1_________________ , TO(0)  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
______________OVERWATCH_L2_________________ , OW_PU  , OW_HG   , OW_SULT , XXXXXXX , XXXXXXX , XXXXXXX ,
______________OVERWATCH_L3_________________ , OW_YES , OW_NO   , OW_HLV  , OW_HLZ  , XXXXXXX , XXXXXXX ,
______________OVERWATCH_L4_________________ , KC_SPACE, OW_GR  , OW_GG   , OW_LGG  , OW_WDA  , OW_LW   , OW_VIO
), // Note: visualizer expects this closing parens to be right at the start of the line.

// Run `./qmk show levinson` from parent dir to see this layer.
[_NAVI] = LAYOUT_ortho_4x12_wrapper(
XXXXXXX , _________________NAVI_L1___________________ , _________________NAVI_R1___________________ , XXXXXXX ,
XXXXXXX , _________________NAVI_L2___________________ , _________________NAVI_R2___________________ , XXXXXXX ,
XXXXXXX , _________________NAVI_L3___________________ , _________________NAVI_R3___________________ , XXXXXXX ,
XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , APPS    , KC_LGUI , MODSFT  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
), // Note: visualizer expects this closing parens to be right at the start of the line.

};

#define OW_MACRO(str) SEND_STRING(SS_TAP(X_ENTER)(str)SS_TAP(X_ENTER));

// called by QMK during key processing before the actual key event is handled. Useful for macros.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOCK:
      if (record->event.pressed) {
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
      }
      return true; // Let QMK send the press/release events
      break;
    case RESET: // TODO: This doesn't actually enter bootloader mode, fix this.
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(song_goodbye);
        #endif
      }
      return true; // Let QMK send the press/release events
      break;

    case CLEAR_EEPROM:
      eeconfig_init();
      #ifdef AUDIO_ENABLE
        PLAY_SONG(song_goodbye); // TODO write custom song if firmware has space
      #endif
      return false; // QMK doesn't know about this keycode
      break;
    case TAP_TOG_LAYER:
      process_tap_tog(_SYMB,record);
      return false;
      break;
    case OW_GR:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER)"gr"SS_TAP(X_ENTER));
      }
      break;
    case OW_GG:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER)"gr"SS_TAP(X_ENTER));
      }
      break;
    case OW_LGG:
      if (record->event.pressed) {
        OW_MACRO("LOL, gg")
      }
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
  #ifdef AUDIO_ENABLE
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(song_startup);
  #endif
  #ifdef RGBLIGHT_ENABLE
    keyboard_post_init_rgb();
  #endif
}

void shutdown_user() {
  #ifdef AUDIO_ENABLE
  PLAY_SONG(song_goodbye);
    _delay_ms(150);
    stop_all_notes();
  #endif
}
