#include <stdint.h>
#include "snowfox.h"

enum anne_pro_layers {
  _BASE_LAYER,
  _MAC_LAYER,
  _FN_LAYER,
};

// This is ROW*MATRIX_COLS + COL
#define CAPS_LOCATION (MATRIX_COLS * 2 + 0)

//Shortcuts for snowfox specific bindings.
//ble discover, connect, disconnect
#define SF_BLE1 SNOWFOX_BLE_DISCOVER
#define SF_BLE2 SNOWFOX_BLE_CONN
#define SF_BLE3 SNOWFOX_BLE_DISCONN
//on, off, next effect
#define SF_LON SNOWFOX_LED_ON
#define SF_LOFF SNOWFOX_LED_OFF
#define SF_LN SNOWFOX_LED_NEXT
//brightness
#define SF_LBD SNOWFOX_LED_BDN
#define SF_LBU SNOWFOX_LED_BUP
//led on and off

//frequency
#define SF_LPD SNOWFOX_LED_PDN
#define SF_LPU SNOWFOX_LED_PUP

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  * Layer _BASE_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | FN      |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  Win   |  Alt  |               space             |  Alt  |  FN  |  App  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  * RShift, FN, App, RCtrl act as arrows when tapped.
  */
  [_BASE_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,   KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,  KC_BSLS,
    MO(_FN_LAYER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT,KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
    KC_LCTL,KC_LGUI, KC_LALT,      KC_SPC,  KC_RALT, LT(_FN_LAYER, KC_LEFT),  MT(KC_APP, KC_DOWN), RCTL_T(KC_RIGHT)
  ),
  /*
  * Layer _MAC_LAYER
  * Same as above but swap LGUI and LALT
  */
  [_MAC_LAYER] = KEYMAP( /* Base */
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LGUI, KC_LALT,      KC_TRNS,             KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS
  ),

  /* Layer _FN_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * | GRV | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   DEL     |
  * |-----------------------------------------------------------------------------------------+
  * | CAPS  | PGU | ^ | PGD | Loff | Lon |      | PGU |  ^  | PGD | PSCR | SCLK | PAUS | LEDn |
  * |-----------------------------------------------------------------------------------------+
  * |         |  <  |  v  |  >  | LBD | LBU | HOM | <   |  v  | ->  | INS | DEL |             |
  * |-----------------------------------------------------------------------------------------+
  * |           | BT1 | BT2 | BT3 |     |     | END |    | Vo- | Vo+  | VoM |                 |
  * |-----------------------------------------------------------------------------------------+
  * |       |       |       |                                 |       |       |      |        |
  * \-----------------------------------------------------------------------------------------/
  */
  [_FN_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_CAPS, KC_PGUP, KC_UP, KC_PGDN, SF_LON, SF_LOFF, KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_PSCR, KC_SLCK, KC_PAUS, SF_LN,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, SF_LBD, SF_LBU, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, SF_BLE1, SF_BLE2, SF_BLE3, SF_LPD, SF_LPU, KC_END, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS
  ),
};

const uint16_t keymaps_size = sizeof(keymaps);


void dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_MAC_LAYER);
      } else {
        layer_off(_MAC_LAYER);
      }
      break;
  }
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}

bool led_update_user(led_t leds) {
  return true;
}
