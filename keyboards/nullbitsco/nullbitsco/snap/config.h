/* Copyright 2021 Jay Greco
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
// clang-format off
#pragma once

/* Used to set host for remote KB if VUSB detect doesn't work. */
// #define KEYBOARD_HOST // Force host mode
// #define KEYBOARD_REMOTE // Force remote mode

// Workarounds for sleep/wake issues
#define USB_SUSPEND_WAKEUP_DELAY 250

/* split config */
// #define SPLIT_USB_DETECT // Enable if you have issues with USB
#define DISABLE_SYNC_TIMER
#define SPLIT_HAND_PIN_LOW_IS_LEFT

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 9
#define MATRIX_MUX_COLS 3

/* Optional split transactions */
#define SPLIT_OLED_ENABLE
