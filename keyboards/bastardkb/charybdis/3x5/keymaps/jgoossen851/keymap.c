/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NUMPAD,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
    LAYER_FUNCTION,
    LAYER_POINTER_OSL,
    LAYER_MEDIA,
    LAYER_NAVIGATION,
    LAYER_TOOL,
    LAYER_POINTER_TO,
};

// Automatically enable sniping-mode on the pointer layer.
#define LAYER_MASK(layer) ((layer_state_t)1 << layer)
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK ( LAYER_MASK(LAYER_POINTER_OSL) | LAYER_MASK(LAYER_POINTER_TO) )

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif      // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define OSM_SFT OSM(MOD_LSFT)
// #define OSM_CTL OSM(MOD_LCTL)
#define OSL_SYM OSL(LAYER_SYMBOLS)
#define OSL_NUM OSL(LAYER_NUMERAL)
#define OSL_NAV OSL(LAYER_NAVIGATION)
#define OSL_PNT OSL(LAYER_POINTER_OSL)
#define OSL_FUN OSL(LAYER_FUNCTION)
#define OSL_TOL OSL(LAYER_TOOL)
#define OSL_PT2 OSL(LAYER_POINTER_TO)
#define AST_ALT MT(KC_ASTR, MOD_LALT)

#define TO_ALPH TO(LAYER_BASE)
#define TO_SYMB TO(LAYER_SYMBOLS)
#define TO_NUMB TO(LAYER_NUMERAL)
#define TO_NAVG TO(LAYER_NAVIGATION)
#define TO_PNTR TO(LAYER_POINTER_OSL)
#define TO_FUNC TO(LAYER_FUNCTION)
#define TO_MEDA TO(LAYER_MEDIA)
#define TO_HXNP TO(LAYER_NUMPAD)
#define TO_TOOL TO(LAYER_TOOL)
#define TO_PTR2 TO(LAYER_POINTER_TO)

#define MO_PNTR MO(LAYER_POINTER_OSL)
#define LNAV    LAYER_NAVIGATION
#define LMED    LAYER_MEDIA

// clang-format off
/** \brief Dvorak layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                          \
        KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,     KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
           KC_A,    KC_O,    KC_E,    KC_U,    KC_I,     KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
        KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,     KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                          XXXXXXX,  KC_SPC, OSL_PNT,  OSL_NUM, OSL_SYM

/** Convenience row shorthands. */
#define _REDO   LCTL(KC_Y)
#define _PASTE  LCTL(KC_V)
#define _COPY   LCTL(KC_C)
#define _CUT    LCTL(KC_X)
#define _UNDO   LCTL(KC_Z)

#define ___X________X__DEAD_HALF_ROW__X________X___  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ___X_______DEAD_KEYS_IV_______X___           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define          ___HOME_ROW_MODS_ACS_L___                    KC_LALT, KC_LCTL, KC_LSFT
#define          ___HOME_ROW_MODS_ACS_R___                    KC_RSFT, KC_RCTL, KC_LALT
#define ________________CLIPBOARD_L________________    _UNDO,    _CUT,   _COPY,  _PASTE,   _REDO
#define ________________CLIPBOARD_R________________    _REDO,    _CUT,   _COPY,  _PASTE,   _UNDO

/*
 * Layers used on the Charybdis Nano.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */


/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                   \
     KC_ESC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_DEL, KC_SLSH, KC_QUES, XXXXXXX, KC_BSPC, \
     KC_TAB,  KC_DLR, KC_PERC, KC_CIRC, KC_MINS,  CAPSWRD, ___HOME_ROW_MODS_ACS_R___,  KC_ENT, \
    KC_LBRC, KC_EXLM,   KC_AT, KC_HASH, KC_RBRC,  KC_CAPS, TO_SYMB, TO_NAVG, OSL_FUN, KC_RGUI, \
                      _______, TO_ALPH, OSL_PNT,  TO_NUMB, TO_SYMB


/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                   \
     KC_ESC,    KC_7,    KC_8,    KC_9,  KC_EQL,   KC_DEL, KC_SLSH,    KC_0, KC_PDOT, KC_BSPC, \
     KC_TAB,    KC_4,    KC_5,    KC_6, KC_MINS,  KC_COLN, OSM_SFT, KC_RCTL, KC_LALT,  KC_ENT, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,  XXXXXXX, TO_NUMB, TO_PNTR, TO_HXNP, KC_RGUI, \
                      _______, TO_ALPH, OSL_PNT,  TO_NUMB, OSL_SYM


/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                                \
     KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP,   KC_DEL, KC_HOME,   KC_UP,  KC_END, KC_BSPC, \
     KC_TAB, ___HOME_ROW_MODS_ACS_L___, KC_PGDN,   KC_INS, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT, \
    KC_LGUI, OSL_TOL, TO_SYMB, TO_NAVG, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, TO_ALPH, OSL_PT2,  TO_NUMB, TO_SYMB


/** \brief Mouse emulation and pointer functions. 
 *
 * Secondary right-hand layer
 */
#define LAYOUT_LAYER_POINTER(f)                                                                   \
     KC_ESC, DPI_MOD, DRGSCRL, SNP_TOG, KC_WH_U,   KC_DEL, KC_WH_L, DRG_TOG, KC_WH_R, KC_BSPC, \
     KC_TAB, ___HOME_ROW_MODS_ACS_L___, KC_WH_D,   KC_INS, KC_BTN1, KC_BTN2, KC_BTN3,  KC_ENT, \
    KC_LGUI, f(LMED), TO_NUMB, TO_PNTR, S_D_MOD,  ________________CLIPBOARD_R________________, \
                      _______, TO_ALPH, f(LNAV),  TO_NUMB, TO_SYMB


/**
 * \brief Function layer.
 *
 * Quaternary left-hand layer has function keys in the same locations as the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner column.
 * Layer is activated pressing both the secondary thumb key (symbols) and the right pinky
 * home-row key (pointer) key simultaneously.
 * App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_FUNCTION                                                                  \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,  XXXXXXX, XXXXXXX,  KC_APP, XXXXXXX, XXXXXXX, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SLCK,  XXXXXXX, ___HOME_ROW_MODS_ACS_R___, XXXXXXX, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,  XXXXXXX, TO_FUNC, TO_TOOL, XXXXXXX, KC_RGUI, \
                      _______, TO_ALPH, OSL_PNT,  TO_NUMB, TO_SYMB


/**
 * \brief Media layer.
 *
 */
#define LAYOUT_LAYER_MEDIA                                                                     \
    ___X________X__DEAD_HALF_ROW__X________X___,  XXXXXXX, KC_MSTP, KC_MPLY, XXXXXXX, XXXXXXX, \
    ___X________X__DEAD_HALF_ROW__X________X___,  KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    XXXXXXX, XXXXXXX, TO_HXNP, TO_MEDA, XXXXXXX,  ___X________X__DEAD_HALF_ROW__X________X___, \
                      _______, TO_ALPH, OSL_PT2,  TO_NUMB, TO_SYMB


/**
 * \brief Number Pad layer.
 *
 * Tertiary left-hand layer has a hexadecimal number pad with digits in the same locations as
 * the digits on the Number Layer. The digits A - C are on the outer column with the same
 * locations as F10 - F12 on the Function Layer and D - F are on the inner column.
 * Numbers in this layer use the dedicated numpad keys; therefore, shifted symbols will not
 * work on this layer but Alt-codes can be used on Windows.
 */
#define LAYOUT_LAYER_NUMPAD                                                                    \
       KC_C, KC_KP_7, KC_KP_8, KC_KP_9,    KC_F,   KC_DEL, KC_SLSH, KC_KP_0, KC_PDOT, KC_BSPC, \
       KC_B, KC_KP_4, KC_KP_5, KC_KP_6,    KC_E,  KC_COLN, KC_ASTR, KC_MINS, KC_PLUS, KC_PENT, \
       KC_A, KC_KP_1, KC_KP_2, KC_KP_3,    KC_D,  KC_CAPS, TO_HXNP, TO_MEDA, XXXXXXX,  KC_NUM, \
                      _______, TO_ALPH, OSL_PNT,  OSL_NUM, OSL_SYM

/**
 * \brief Tools layer.
 *
 */
#define LAYOUT_LAYER_TOOL                                                                      \
    ___X________X__DEAD_HALF_ROW__X________X___,   EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, \
    ___X________X__DEAD_HALF_ROW__X________X___,  ___X________X__DEAD_HALF_ROW__X________X___, \
    XXXXXXX, XXXXXXX, TO_FUNC, TO_TOOL, XXXXXXX,  ___X________X__DEAD_HALF_ROW__X________X___, \
                      _______, TO_ALPH, OSL_PT2,  TO_NUMB, TO_SYMB


/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _ACS_L(kc1, kc2, kc3) LALT_T(kc1), LCTL_T(kc2), LSFT_T(kc3)
#define _ACS_R(kc1, kc2, kc3) RSFT_T(kc1), RCTL_T(kc2), LALT_T(kc3)
#define _LG(kc) LGUI_T(kc)
#define _RG(kc) RGUI_T(kc)
#define _HOME_ROW_MOD_GACS(                                                     \
    L00, L01, L02, L03, L04,   R05, R06, R07, R08, R09,                         \
    L10, L11, L12, L13, L14,   R15, R16, R17, R18, R19,                         \
    L20, L21, L22, L23, L24,   R25, R26, R27, R28, R29,                         \
    ...)                                                                        \
        L00,        L01, L02, L03,  L04,   R05,        R06, R07, R08,     R09,  \
        L10, _ACS_L(L11, L12, L13), L14,   R15, _ACS_R(R16, R17, R18),    R19,  \
    _LG(L20),       L21, L22, L23,  L24,   R25,        R26, R27, R28, _RG(R29), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE]       = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE)),
  [LAYER_SYMBOLS]    = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_NUMERAL]    = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_POINTER_OSL]    = LAYOUT_wrapper(LAYOUT_LAYER_POINTER(OSL)),
  [LAYER_FUNCTION]   = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_MEDIA]      = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NUMPAD]     = LAYOUT_wrapper(LAYOUT_LAYER_NUMPAD),
  [LAYER_TOOL]       = LAYOUT_wrapper(LAYOUT_LAYER_TOOL),
  [LAYER_POINTER_TO]  = LAYOUT_wrapper(LAYOUT_LAYER_POINTER(TO)),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif  // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_kb(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
#        endif  // RGB_MATRIX_ENABLE
    }
    matrix_scan_user();
}
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif      // POINTING_DEVICE_ENABLE

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK
    charybdis_set_pointer_sniping_enabled(state & (CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK));
#    endif  // CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK
#endif      // POINTING_DEVICE_ENABLE
    switch (get_highest_layer(state)) {
        case LAYER_BASE:
            LED_OFF(LED_1);
            LED_OFF(LED_2);
            LED_OFF(LED_3);
            LED_OFF(LED_4);
            break;
        case LAYER_NAVIGATION:
        case LAYER_POINTER_OSL:
            LED_OFF(LED_1);
            LED_ON(LED_2);
            LED_OFF(LED_3);
            LED_ON(LED_4);
            break;
        case LAYER_SYMBOLS:
        case LAYER_NUMERAL:
            LED_ON(LED_1);
            LED_OFF(LED_2);
            LED_ON(LED_3);
            LED_OFF(LED_4);
            break;
        default:
            LED_ON(LED_1);
            LED_ON(LED_2);
            LED_ON(LED_3);
            LED_ON(LED_4);
            break;
    }
    return state;
}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!host_keyboard_led_state().num_lock)  {
        // Turn on Num Lock if the computer indicates it is off
        register_code(KC_NLCK);
        unregister_code(KC_NLCK);
    }
    // Your macros...

    return true;
}

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb_red();
#endif  // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
}
