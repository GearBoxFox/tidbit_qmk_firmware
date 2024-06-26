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
#pragma once

/* RP2040-specific defines*/
#define RP2040_FLASH_W25X10CL
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define RMKB_SIO_DRIVER SIOD0
#define RMKB_SIO_TX_PIN GP0
#define RMKB_SIO_RX_PIN GP1

// define encoders
#define ENCODERS_PAD_A { GP23 }
#define ENCODERS_PAD_B { GP20 }

// "encoder": {
//         "rotary": [
//             {"pin_a": "GP23", "pin_b": "GP20"},
//             {"pin_a": "GP8", "pin_b": "GP9"},
//             {"pin_a": "GP3", "pin_b": "GP2"},
//             {"pin_a": "GP0", "pin_b": "GP1"}
//         ]
//     },
