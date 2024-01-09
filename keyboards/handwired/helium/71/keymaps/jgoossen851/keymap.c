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


/* Home-Row Mods */
#define _GACS_L(kc1, kc2, kc3, kc4) LGUI_T(kc1), LALT_T(kc2), LCTL_T(kc3), LSFT_T(kc4)
#define _GACS_R(kc1, kc2, kc3, kc4) RSFT_T(kc1), RCTL_T(kc2), LALT_T(kc3), LGUI_T(kc4)
#define _APPLY_HOME_ROW_MODS_GACS(                                                        \
  k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H,   k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H,       \
  k1A,   k1B, k1D, k1E, k1F, k1G, k1H,   k6A, k6B, k6C, k6D, k6E, k6F, k6G,    k6H,       \
  k2A,    k2B, k2D, k2E, k2F, k2G, k2H,   k7A, k7B, k7C, k7D, k7E, k7F,        k7H,       \
  ...)                                                                                    \
  k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H,         \
  k1A, k1B, k1D, k1E, k1F, k1G, k1H, k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H,              \
  k2A, k2B, _GACS_L(k2D, k2E, k2F, k2G), k2H, k7A, _GACS_R(k7B, k7C, k7D, k7E), k7F, k7H, \
  __VA_ARGS__
#define APPLY_HOME_ROW_MODS_GACS(...) _APPLY_HOME_ROW_MODS_GACS(__VA_ARGS__)
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)


enum helium_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RIGHT,
    LAYER_LEFT,
};

#define LOWER MO(LAYER_LOWER)
#define LEFT  MO(LAYER_LEFT)
#define RIGHT MO(LAYER_RIGHT)

#if SOFTWARE_DVORAK_MAPPING
#  define DV_COLN RSFT(KC_Z)
#else
#  define DV_COLN KC_COLN
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// BASE LAYER (the 5 leftmost keys are optional and can be set in custom layout)
  [LAYER_BASE] = LAYOUT_wrapper(APPLY_HOME_ROW_MODS_GACS(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮    ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
      XXXXXXX,  KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,         KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,  KC_GRV, KC_BSPC,
  // ├────────┼────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┼────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴────────┤
      XXXXXXX,      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,      KC_BSLS,
  // ├────────┼────────────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──╮ ╰──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴─────────────┤
      XXXXXXX,        CW_TOGG, KC_A, KC_S,  KC_D,   KC_F,    KC_G,         KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,             KC_ENT,
  // ├────────┼────────┬──────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───╮╰───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴──────────┬────────┤
      XXXXXXX,   RIGHT,   KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,        KC_RSFT,    LEFT,
  // ├────────┼────────┴─┬────────┴─┬──────┴───┬────┴─────┬──┴────────┴────────┤    ├────────┴────────┴───────┬┴────────┴┬───────┴──┬──────────┬─┴────────┤
      XXXXXXX,   KC_RCTL,   KC_LGUI,   KC_LALT,     LOWER,              KC_SPC,                        KC_SPC,   KC_LALT,   KC_LGUI,    KC_APP,   KC_RCTL
  // ╰────────┴──────────┴──────────┴──────────┴──────────┴────────────────────╯    ╰─────────────────────────┴──────────┴──────────┴──────────┴──────────╯
  )),

  // NAVIGATION LAYER (based on vim HJKL navigation with inverted-T option)
  [LAYER_LOWER] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮    ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
      XXXXXXX,  KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,      XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  // ├────────┼────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┼────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴────────┤
      XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
  // ├────────┼────────────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──╮ ╰──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴─────────────┤
      XXXXXXX,        XXXXXXX, KC_LGUI, KC_LALT, KC_RCTL, KC_LSFT, XXXXXXX,      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,  KC_INS,             KC_ENT,
  // ├────────┼────────┬──────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───╮╰───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴──────────┬────────┤
      XXXXXXX, XXXXXXX,   KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL,          KC_UP, XXXXXXX,
  // ├────────┼────────┴─┬────────┴─┬──────┴───┬────┴─────┬──┴────────┴────────┤    ├────────┴────────┴───────┬┴────────┴┬───────┴──┬──────────┬─┴────────┤
      XXXXXXX,   KC_RCTL,   KC_LGUI,   KC_LALT,   _______,             XXXXXXX,                       XXXXXXX,   XXXXXXX,   KC_LEFT,   KC_DOWN,   KC_RGHT
  // ╰────────┴──────────┴──────────┴──────────┴──────────┴────────────────────╯    ╰─────────────────────────┴──────────┴──────────┴──────────┴──────────╯
  ),

  // NUMBER PAD
  [LAYER_LEFT] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮    ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
      XXXXXXX,  KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS,      QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  // ├────────┼────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┼────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴────────┤
      XXXXXXX,      KC_TAB, XXXXXXX,   KC_P7,   KC_P8,   KC_P9, KC_PPLS,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
  // ├────────┼────────────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──╮ ╰──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴─────────────┤
      XXXXXXX,        KC_PENT, XXXXXXX,   KC_P4,   KC_P5,   KC_P6, KC_PEQL,      XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_LGUI, XXXXXXX,             KC_ENT,
  // ├────────┼────────┬──────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───╮╰───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴──────────┬────────┤
      XXXXXXX, XXXXXXX,   KC_LSFT, XXXXXXX,   KC_P1,   KC_P2,   KC_P3, DV_COLN,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        KC_RSFT, _______,
  // ├────────┼────────┴─┬────────┴─┬──────┴───┬────┴─────┬──┴────────┴────────┤    ├────────┴────────┴───────┬┴────────┴┬───────┴──┬──────────┬─┴────────┤
      XXXXXXX,   KC_RCTL,   KC_LGUI,   KC_LALT,   KC_PDOT,               KC_P0,                       XXXXXXX,   KC_LALT,   KC_LGUI,    KC_APP,   KC_RCTL
  // ╰────────┴──────────┴──────────┴──────────┴──────────┴────────────────────╯    ╰─────────────────────────┴──────────┴──────────┴──────────┴──────────╯
  ),

  // FUNCTIONS
  [LAYER_RIGHT] = LAYOUT(
  // ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮    ╭────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────╮
      XXXXXXX,  KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, KC_BSPC,
  // ├────────┼────────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┼────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴────────┤
      XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
  // ├────────┼────────────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──╮ ╰──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴──┬─────┴─────────────┤
      XXXXXXX,        XXXXXXX, KC_LGUI, KC_LALT, KC_RCTL, KC_LSFT, XXXXXXX,      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,             KC_ENT,
  // ├────────┼────────┬──────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───╮╰───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴───┬────┴──────────┬────────┤
      XXXXXXX, _______,   KC_LSFT, XXXXXXX,  KC_CUT, KC_COPY, KC_PSTE, XXXXXXX,      XXXXXXX, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX,        KC_RSFT, XXXXXXX,
  // ├────────┼────────┴─┬────────┴─┬──────┴───┬────┴─────┬──┴────────┴────────┤    ├────────┴────────┴───────┬┴────────┴┬───────┴──┬──────────┬─┴────────┤
      XXXXXXX,   KC_RCTL,   KC_LGUI,   KC_LALT,   XXXXXXX,             XXXXXXX,                       XXXXXXX,   KC_LALT,   KC_LGUI,    KC_APP,   KC_RCTL
  // ╰────────┴──────────┴──────────┴──────────┴──────────┴────────────────────╯    ╰─────────────────────────┴──────────┴──────────┴──────────┴──────────╯
  ),
};
// clang-format on


/* Caps Word */
#ifdef CAPS_WORD_ENABLE

void caps_word_set_user(bool active) {
    if (active) {
        // Do something when Caps Word activates.
    } else {
        // Do something when Caps Word deactivates.
    }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
#if SOFTWARE_DVORAK_MAPPING
        // E,Q,W,Z map to punctuation, and should be excluded
        case KC_A ... KC_D:
        case KC_F ... KC_P:
        case KC_R ... KC_V:
        case KC_X ... KC_Y:
        // ,./; map to letters and should be included
        case KC_COMM:
        case KC_DOT:
        case KC_SLSH:
        case KC_SCLN:
        // ' maps to hyphen and should be included for underscores
        case KC_QUOT:
#else
        case KC_A ... KC_Z:
        case KC_MINS:
#endif
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_KP_1 ... KC_KP_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
#endif // CAPS_WORD_ENABLE
