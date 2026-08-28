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


#include "propergol.h"

static uint16_t next_keycode;
static keyrecord_t next_record;

bool get_speculative_hold(uint16_t keycode, keyrecord_t* record) {

    // Disable speculative hold during tapping sequences
    if (get_idle_time() < FLOW_TAP_INTERVAL) { return false; }
    // Disable speculative hold when any mods are already active
    // not to mess with hotkeys
    if (get_mods() | get_oneshot_mods()) { return false; }

    // Enable speculative holding for these keys.
    switch (keycode) {
        case I(PG_T):
        case I(PG_N):
            return true;
    }
    return false;  // Disable otherwise.
}

bool is_tapping_sequence(uint16_t keycode) {
    // To trigger Tap Flow, the last input must be a character,
    // the time between the keypresses must be lower than FLOW_TAP_INTERVAL
    // and the ongoing keypress must be on a layer used for characters with mod-tap keys on it
    if (get_recent_keycode(-1) == KC_NO) { return false; }
    if (get_idle_time() > FLOW_TAP_INTERVAL) { return false; }
    
    switch (get_highest_layer(layer_state)) {
        case _BASE:
        case _NUMBERS:
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
            return 300;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
        case LT_SPC:
            return 150;
        default:
            return QUICK_TAP_TERM;
    }
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    CHORDAL_HOLD_KAWA_LAYOUT(
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*', '*', 'R', '*'
    );

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    // Exceptionally allow some one-handed chords for hotkeys.
    switch (tap_hold_keycode) {
        case LT_SPC:
            if (other_keycode == PG_X) {
                return true;
            }
            break;
    }
    // Otherwise defer to the opposite hands rule.
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Desabling Permissive Hold for `E` when the other key is on the same side
        case LT_E:
            return approved_chord(keycode, record, next_keycode, &next_record);
        default:
            return true;
    }
}


// Housekeeping

void housekeeping_task_user(void) {
    modword_task();
}


// Key processing

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
      // Cache the next input for mod-tap decisions
      next_keycode = keycode;
      next_record  = *record;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // LT Repeat and Magic keys
    if (!process_macros_I(keycode, record)) { return false; }

    // Prefixed layers
    if (!process_prefixing_layers(keycode, record)) { return false; }

    // Clever keys
    process_clever_keys(keycode, record);

    // Caps Word
    if (!process_modword(keycode, record)) {return false; }

    // Other macros
    if (!process_macros_II(keycode, record)) { return false; }

    // Process all other keycodes normally
    return true;
}