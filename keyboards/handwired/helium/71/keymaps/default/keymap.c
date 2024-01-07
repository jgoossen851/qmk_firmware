/**
 * Copyright 2024 Jeremy Goossen (@jgoossen851)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum helium_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)

#define CTL_BSP CTL_T(KC_BSPC)
#define SFT_SPC SFT_T(KC_SPC)
#define GUI_ENT GUI_T(KC_ENT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮    ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
       KC_INS,  KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,         KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV,
  // ├────────┼────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┼────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴────────┤
       KC_DEL,      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,      KC_BSPC,
  // ├────────┼────────────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──╮ ╰──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴─────────────┤
      KC_HOME,        KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,             KC_ENT,
  // ├────────┼────────┬──────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───╮╰───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴──────────┬────────┤
       KC_END,   LOWER,   KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,        KC_RSFT,   RAISE,
  // ├────────┼────────┴─┬────────┴─┬──────┴───┬────┴─────┬──┴────────┴────────┤    ├────────┴────────┴───────┬┴────────┴┬───────┴──┬──────────┬─┴────────┤
        LOWER,   KC_RCTL,   KC_LGUI,   KC_LALT,     LOWER,              KC_SPC,                        KC_SPC,   KC_RALT,   KC_LGUI,    KC_APP,   KC_RCTL
  // ╰────────┴──────────┴──────────┴──────────┴──────────┴────────────────────╯    ╰─────────────────────────┴──────────┴──────────┴──────────┴──────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮    ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
      RGB_TOG, KC_MNXT, KC_MPLY,    KC_R,    KC_R,    KC_R, KC_MPRV, XXXXXXX,      KC_LBRC,    KC_R,    KC_R,    KC_R,    KC_7,    KC_8,    KC_9, KC_RBRC,
  // ├────────┼────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┼────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴────────┤
      KC_LGUI,     KC_LALT,    KC_F,    KC_F,    KC_F, KC_LSFT, XXXXXXX,      KC_PPLS,    KC_F,    KC_F,    KC_F,    KC_4,    KC_5,    KC_6,      KC_PMNS,
  // ├────────┼────────────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──╮ ╰──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴─────────────┤
      XXXXXXX,           KC_V,    KC_V,    KC_V,  EE_CLR, QK_BOOT, KC_PAST,         KC_V,    KC_V,    KC_V,    KC_1,    KC_2,    KC_3,            KC_PSLS,
  // ├────────┼────────┬──────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───╮╰───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴──────────┬────────┤
         KC_Z, _______,      KC_C,    KC_V,    KC_V,    KC_V,    KC_V,    KC_B,         KC_N,    KC_V,    KC_V,    KC_V,    KC_M,          KC_UP, XXXXXXX,
  // ├────────┼────────┴─┬────────┴─┬──────┴───┬────┴─────┬──┴────────┴────────┤    ├────────┴────────┴───────┬┴────────┴┬───────┴──┬──────────┬─┴────────┤
      _______,   SFT_SPC,   SFT_SPC,   SFT_SPC,   _______,             SFT_SPC,                       SFT_SPC,   SFT_SPC,   KC_LEFT,   KC_DOWN,   KC_RGHT
  // ╰────────┴──────────┴──────────┴──────────┴──────────┴────────────────────╯    ╰─────────────────────────┴──────────┴──────────┴──────────┴──────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮    ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_R,    KC_R,    KC_R, XXXXXXX,      XXXXXXX,    KC_R,    KC_R,    KC_R, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX,
  // ├────────┼────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┼────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴────────┤
      KC_LEFT,       KC_UP, KC_DOWN, KC_RGHT,    KC_F,    KC_F,    KC_F,      XXXXXXX,    KC_F,    KC_F,    KC_F, KC_RSFT, KC_RCTL, KC_RALT,      KC_RGUI,
  // ├────────┼────────────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──╮ ╰──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴─────────────┤
      KC_HOME,        KC_PGUP, KC_PGDN,  KC_END,    KC_V,    KC_V,    KC_V,      QK_BOOT,    KC_V,    KC_V,    KC_V,  EE_CLR, XXXXXXX,            XXXXXXX,
  // ├────────┼────────┬──────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───╮╰───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴──────────┬────────┤
         KC_Z,    KC_X,      KC_C,    KC_V,    KC_V,    KC_V,    KC_V,    KC_B,         KC_N,    KC_V,    KC_V,    KC_M, KC_COMM,         KC_DOT, _______,
  // ├────────┼────────┴─┬────────┴─┬──────┴───┬────┴─────┬──┴────────┴────────┤    ├────────┴────────┴───────┬┴────────┴┬───────┴──┬──────────┬─┴────────┤
      _______,   _______,   SFT_SPC,   SFT_SPC,   SFT_SPC,             SFT_SPC,                       SFT_SPC,   _______,   SFT_SPC,   SFT_SPC,   SFT_SPC
  // ╰────────┴──────────┴──────────┴──────────┴──────────┴────────────────────╯    ╰─────────────────────────┴──────────┴──────────┴──────────┴──────────╯
  ),
};
// clang-format on
