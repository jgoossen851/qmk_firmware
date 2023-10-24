/*
 * Copyright 2023 Jeremy Goossen (@jgoossen851)
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

/* Handedness */
#define SPLIT_HAND_MATRIX_GRID F7, C6
#define MATRIX_MASKED
// Left Hand [Top 5 Rows] (LSB = outside key), Right Hand [Bottom 5 Rows]
#define MATRIX_MASK { \
    0b11111, \
    0b11111, \
    0b11111, \
    0b11100, \
    0b11111, \
    0b11111, \
    0b11111, \
    0b11000, \
}
