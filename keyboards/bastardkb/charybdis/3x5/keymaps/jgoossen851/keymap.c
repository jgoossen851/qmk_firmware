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

#include "features/layer_lock.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum custom_keycodes {
        LLOCK = SAFE_RANGE,
    // Other custom keys...
};

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NAVIGATION,
    LAYER_POINTER,
    LAYER_MEDIA,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
    LAYER_FUNCTION,
};

// Automatically enable sniping-mode on the pointer layer.
#define LAYER_MASK(layer) ((layer_state_t)1 << layer)
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK LAYER_MASK(LAYER_POINTER)

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif      // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_PTR LT(LAYER_POINTER, KC_TAB)
#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
// #define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define FCN_LAY MO(LAYER_FUNCTION)
#define _L_BTN(KC) LT(LAYER_POINTER, KC)

// clang-format off
/** \brief Dvorak layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                          \
        KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,     KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
           KC_A,    KC_O,    KC_E,    KC_U,    KC_I,     KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
        KC_COLN,    KC_Q,    KC_J,    KC_K,    KC_X,     KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                          ESC_MED, SPC_NAV, TAB_PTR,  ENT_SYM, BSP_NUM

/** Convenience row shorthands. */
#define _REDO   LCTL(KC_Y)
#define _PASTE  LCTL(KC_V)
#define _COPY   LCTL(KC_C)
#define _CUT    LCTL(KC_X)
#define _UNDO   LCTL(KC_Z)

#define ___X________X__DEAD_HALF_ROW__X________X___  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ___X_______DEAD_KEYS_IV_______X___           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define          _____HOME_ROW_MODS_L______________           KC_LALT, KC_LCTL, KC_LSFT, KC_RALT
#define ______________HOME_ROW_MODS_R_____           KC_RALT, KC_LSFT, KC_LCTL, KC_LALT
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
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                                \
    ___X________X__DEAD_HALF_ROW__X________X___,   KC_INS, KC_HOME,   KC_UP,  KC_END, KC_PGUP, \
    XXXXXXX, _____HOME_ROW_MODS_L______________,  KC_CLCK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, \
    KC_LGUI, XXXXXXX, XXXXXXX,   LLOCK, XXXXXXX,  ________________CLIPBOARD_R________________, \
                      XXXXXXX, _______, XXXXXXX,   KC_ENT, KC_BSPC

/** \brief Mouse emulation and pointer functions. 
 *
 * Secondary right-hand layer
 */
#define LAYOUT_LAYER_POINTER                                                                   \
    DPI_MOD, XXXXXXX, DRGSCRL, SNIPING, S_D_MOD,  XXXXXXX, KC_WH_L, DRGSCRL, KC_WH_R, KC_WH_U, \
    XXXXXXX, _____HOME_ROW_MODS_L______________,  XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, KC_WH_D, \
    KC_LGUI, XXXXXXX, XXXXXXX,   LLOCK, XXXXXXX,  ________________CLIPBOARD_R________________, \
                      XXXXXXX, KC_BTN1, KC_BTN2,  FCN_LAY,  KC_DEL

/**
 * \brief Media layer.
 *
 * Tertiary right-hand layer is media.

 */
#define LAYOUT_LAYER_MEDIA                                                                     \
    EEP_RST, ___X_______DEAD_KEYS_IV_______X___,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    ___X________X__DEAD_HALF_ROW__X________X___,  KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    XXXXXXX, XXXXXXX, XXXXXXX,   LLOCK, QK_BOOT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, XXXXXXX, XXXXXXX,  KC_MSTP, KC_MPLY


/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                   \
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,  ___X________X__DEAD_HALF_ROW__X________X___, \
    KC_SLSH,    KC_4,    KC_5,    KC_6,  KC_EQL,  ______________HOME_ROW_MODS_R_____, XXXXXXX, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,  XXXXXXX,   LLOCK, XXXXXXX, XXXXXXX, KC_LGUI, \
                       KC_DOT,    KC_0, KC_MINS,  XXXXXXX, _______

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                   \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,  ___X________X__DEAD_HALF_ROW__X________X___, \
    KC_QUES,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,  ______________HOME_ROW_MODS_R_____, FCN_LAY, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE,  XXXXXXX,   LLOCK, XXXXXXX, XXXXXXX, KC_LGUI, \
                      KC_LPRN, KC_RPRN, KC_UNDS,  _______, XXXXXXX

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
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,  ___X________X__DEAD_HALF_ROW__X________X___, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SLCK,  ______________HOME_ROW_MODS_R_____, _______, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,  XXXXXXX,   LLOCK, XXXXXXX, XXXXXXX, KC_LGUI, \
                       KC_APP,  KC_SPC,  KC_TAB,  _______, XXXXXXX

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
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,  LALT_T(L11), LCTL_T(L12), LSFT_T(L13), RALT_T(L14), \
      RALT_T(R15), RSFT_T(R16), RCTL_T(R17), LALT_T(R18),        R19,  \
      LGUI_T(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  RGUI_T(R29), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * \brief Add button layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     BUTTON_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _BUTTON_MOD(                                                   \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      _L_BTN(L10),        L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,  _L_BTN(R19), \
      __VA_ARGS__
#define BUTTON_MOD(...) _BUTTON_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    BUTTON_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
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

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(state & (CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK));
    return state;
}   
#    endif  // CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK
#endif      // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
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
