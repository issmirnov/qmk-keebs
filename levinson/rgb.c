#include "rgb.h"

// TODO gate this debugging header
#include <print.h>

// Wired up in layer_state_set_user in keymap.c
uint32_t layer_state_set_rgb(uint32_t state) {
  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(state);
  if (old_layer != new_layer) {
    switch (new_layer) {
      case _QWERTY:
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv_noeeprom(RGB_CLEAR);
        break;
      case _SYMB:
        rgblight_sethsv_noeeprom_red();
        break;
      case _NUMP:
        rgblight_sethsv_noeeprom_green();
        break;
      case _OVERWATCH:
        rgblight_sethsv_noeeprom_blue();
        // TODO set up animated rainbow swirl with overwatch colors.
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
        // rgblight_effect_breathing(&animation_status);
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;
      case _NAVI:
        rgblight_sethsv_noeeprom(HSV_AZURE);
        break;
      default: //  for any other layers, or the default layer
        break;
    }
    old_layer = new_layer;
  }
  return state;
}


void keyboard_post_init_rgb(void) {
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_setrgb(RGB_CLEAR);
  uprintf("Reset RGB colors");
}

void matrix_scan_rgb(void) {
  set_rgb_indicators(get_mods(), get_oneshot_mods());
}

void set_rgb_indicators(uint8_t this_mod, uint8_t this_osm) {
  if (biton32(layer_state) == _QWERTY) {
    if ((this_mod | this_osm) & MOD_MASK_SHIFT) {
      rgblight_setrgb_gold_at(SHFT_LED1);
    } else {
      rgblight_setrgb_at(RGB_CLEAR, SHFT_LED1);
    }

    if ((this_mod | this_osm) & MOD_MASK_GUI) {
      rgblight_setrgb_purple_at(GUI_LED1);
    } else {
      rgblight_setrgb_at(RGB_CLEAR, GUI_LED1);
    }
  }
}
