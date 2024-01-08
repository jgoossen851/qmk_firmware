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

#pragma once

#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 5000  // 5 seconds

#define SOFTWARE_DVORAK_MAPPING 1 // QWERTY-to-DVORAK done by OS

/**
 * \brief Configure the global tapping term (default: 200ms).
 *
 * If you have a lot of accidental mod activations, crank up the tapping term.
 *
 * See docs.qmk.fm/#/tap_hold?id=tapping-term
 */
#define TAPPING_TERM 200

/**
 * \brief Enable auto-repeat on mod-taps by holding key after quick tap.
 *
 * Set to zero to completely disable auto-repeat.
 *
 * See docs.qmk.fm/#/tap_hold?id=quick-tap-term
 */
#define QUICK_TAP_TERM 120

/**
 * \brief Faster tap-hold trigger.
 *
 * Without `PERMISSIVE_HOLD`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 e🠕 Mod(a)🠕 ➞ ae
 * With `PERMISSIVE_HOLD`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 e🠕 Mod(a)🠕 ➞ Mod+e
 *
 * See docs.qmk.fm/#/tap_hold?id=permissive-hold
 */
#define PERMISSIVE_HOLD
