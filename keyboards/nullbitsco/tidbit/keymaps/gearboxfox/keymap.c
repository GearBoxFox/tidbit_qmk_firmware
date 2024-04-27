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

#include QMK_KEYBOARD_H

// list of layers 
enum layers {
    BASE = 0,
    LED,
    MOD
};

// custom keys 
enum {
    TD_SUPER_MOD_LAYER = PB_1,
    MC_STEAM,
};

// timer for tap-hold super key
#define HOLD_TIME 125
#define LED_ON_TIME 500
static uint32_t hold_timer;
static uint32_t led_timer;
static bool held;
static bool led_blinked;

// list of led layers used for status indicators
// set top two leds to red when LED config layer is open
const rgblight_segment_t PROGMEM led_config_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_RED}
);
// set all leds to blink purple when in MOD layer
const rgblight_segment_t PROGMEM mod_layer_blink[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 8, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    led_config_layer,
    mod_layer_blink
);

// setup basic keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
  TG(LED), KC_PSLS, KC_BSPC,
  KC_P7, KC_P8,   KC_P9,   KC_PPLS,
  KC_P4, KC_P5,   KC_P6,   KC_PMNS,
  KC_P1, KC_P2,   KC_P3,   KC_PAST,
  TD_SUPER_MOD_LAYER, KC_P0, KC_PDOT, KC_PENT
  ),

  [LED] = LAYOUT(
  _______, KC_A, KC_B,
  RGB_TOG, RGB_MOD, RGB_RMOD, RGB_M_P,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  KC_LSFT, RGB_HUI, RGB_SAI, RGB_VAI
  ),

  [MOD] = LAYOUT(
  QK_BOOT, _______, _______,
  KC_MNXT, KC_MPLY, _______, OSM(KC_F),
  KC_MPRV, KC_MSTP, _______, MC_STEAM,
  _______, _______, _______, _______,
  _______, _______, _______, KC_NUM
  ),
};

#ifdef ENCODER_MAP_ENABLE
// handle encoders with a keymap
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), },
    [LED] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), },
    [MOD] = { ENCODER_CCW_CW(_______, _______), },
};
#endif

// handles user post init functions like led config
void keyboard_post_init_user(void) {
    // enable LED layers
    rgblight_layers = rgb_layers;
}

// handles after matrix scan but before keypresses are sent
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // tap-hold configuration
        case TD_SUPER_MOD_LAYER:
            if (record->event.pressed) {
                if (!held) {
                    hold_timer = timer_read32();
                    held = true;
                }
            } else {
                if (timer_elapsed32(hold_timer) < HOLD_TIME) {
                    tap_code(KC_LGUI);
                }
                held = false;
            }
            return false;
        // steam macro
        case MC_STEAM:
            if (record->event.pressed) {
                tap_code_delay(KC_LGUI, 500);
                SEND_STRING(SS_DELAY(500) "steam");
                tap_code_delay(KC_ENTER, 750);
            }

            break;
    }

    return true;
}

// periodic loop
void housekeeping_task_user(void) {
    // check tap-hold for super
    if (held && timer_elapsed32(hold_timer) > HOLD_TIME) {
        layer_on(MOD);

        if (led_blinked) {
            rgblight_set_layer_state(1, timer_elapsed32(led_timer) < LED_ON_TIME);
        } else {
            led_blinked = true;
            led_timer  = timer_read32();
        } 
    } else {
        layer_off(MOD);
        rgblight_set_layer_state(1, false);
        led_blinked = false;
    }
}

// runs after each key press
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    rgblight_set_layer_state(0, layer_state_cmp(layer_state, LED));
    
    if (layer_state_cmp(layer_state, MOD)) {
        rgblight_blink_layer(1, 500);
    }
}
