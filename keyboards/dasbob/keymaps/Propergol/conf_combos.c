/* Copyright 2025 @Kawamashi
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

#include "propergol.h"

enum combos {
  BKSPC, 
  ENTER,
  TAB,
  ESC, 
  ALTTAB,
  CMB_PANIC
};


const uint16_t PROGMEM bkspc_combo_d[] = {PG_C, PG_J, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {PG_F, PG_W, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {PG_EGRV, PG_Y, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {PG_U, PG_EACU, COMBO_END};
const uint16_t PROGMEM alttab_combo[] = {PG_H, PG_Y, COMBO_END};
const uint16_t PROGMEM panic_combo[] = {PG_D, PG_F, COMBO_END};

combo_t key_combos[] = {
    [BKSPC] = COMBO(bkspc_combo_d, KC_BSPC),
    [ENTER] = COMBO(enter_combo, KC_ENT),
    [TAB] = COMBO(tab_combo, KC_TAB),
    [ESC] = COMBO(esc_combo, KC_ESC),
    [CMB_PANIC] = COMBO(panic_combo, PANIC),
    [ALTTAB] = COMBO(alttab_combo, KC_NO),
    };


bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {

    // Some combos should trigger regardless of the idle time.
    switch (combo_index) {
        case BKSPC:
        case ENTER:
          return true;

        default:
          //return enough_time_before_combo();    // takes more space
          if (get_idle_time() < IDLE_TIME_BEFORE_COMBO) { return false; }
    }
    return true;
}


void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
      case ALTTAB:
        if (pressed) {
            register_mods(MOD_LALT);
            tap_code(KC_TAB);
            layer_on(_SHORTNAV);
        } else {
            layer_off(_SHORTNAV);
            unregister_mods(MOD_LALT);
        }
        break;
  }
}

bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
  switch (combo_index) {

      case ALTTAB:
        switch (keycode) {
          case PG_Y:
              tap_code16(S(KC_TAB));
              return true;
          case PG_H:
              tap_code(KC_TAB);
              return true;
        }
        break;
  }
  return false;
}