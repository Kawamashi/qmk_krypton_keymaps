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

#pragma once

#include QMK_KEYBOARD_H

//#include "propergol_keycodes.h"

//#include "features/modword.h"
//#include "../../modules/Kawamashi/layer_word/layer_word.h"
#include "../../modules/Kawamashi/oneshots_on_steroids/oneshots_on_steroids.h"
#include "../../modules/Kawamashi/clever_keys/clever_keys.h"


// conf_words

// Returns true for macros used to type sequence of letters
bool is_send_string_macro(uint16_t keycode);

// Returns true for letters that can be followed by an apostrophe (in french)
bool is_followed_by_apos(uint16_t keycode, uint16_t prev_keycode);


// conf_features

// Returns true if `pos` on the left hand of the keyboard, false if right.
bool on_left_hand(keypos_t pos);

/**
 * Returns true if the args come from keys on opposite hands.
 *
 * @param tap_hold_record keyrecord_t from the tap-hold key's event.
 * @param other_record keyrecord_t from the other key's event.
 * @return True if the keys are on opposite hands.
 */
bool bilateral_combination(const keyrecord_t* tap_hold_record, const keyrecord_t* other_record);

/**
 * Optional callback to customize which key chords are considered "held".
 *
 * This callback is called if while `tap_hold_keycode` is pressed,
 * `other_keycode` is pressed. Return true if the tap-hold key should be
 * considered held, or false to consider it tapped.
 *
 * @param tap_hold_keycode Keycode of the tap-hold key.
 * @param tap_hold_record keyrecord_t from the tap-hold press event.
 * @param other_keycode Keycode of the other key.
 * @param other_record keyrecord_t from the other key's press event.
 * @return True if the tap-hold key should be considered held.
 */
bool approved_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record);

// Handles the tap function of tap-hold keys using non-basic keycodes
bool process_custom_tap_hold(uint16_t keycode, keyrecord_t *record);

// Set whether numbers from numrow are to be replaced by numbers from numpad 
void set_use_numpad(bool target);

// Returns whether numbers from numrow are to be replaced by numbers from numpad
bool should_use_numpad(void);

// This function extracts the base keycode of MT and LT,
// even if the tap/hold key is a custom one, with non-basic tap keycode.
uint16_t tap_hold_extractor(uint16_t keycode);

// Macros to be executed at the beginning of process_record_user :
// Layer-tap Repeat and Magic keys
bool process_macros_I(uint16_t keycode, keyrecord_t *record);

// Other macros, to be executed at the end of process_record_user
bool process_macros_II(uint16_t keycode, keyrecord_t *record);


// Prefixing Layers

/* Handler function for prefixing layers

 * My custom layout uses the One Dead Key (1DK) concept.
 * <https://github.com/OneDeadKey/1dk/blob/master/1dk.md>
 * In my keymap, I use a prefixing layer to implement it.
 * This approach allows more flexibility than to use the 1DK directly.
 * This way, on my 1DK layer, I can use macros or symbols that don’t need the 1DK.
 * 
 * I also use One Shot for All (OS4A) keys and layers. 
 * On their side of the keyboard, OS4A keys behave like one-shot layers, mainly to access Callum mods.
 * OS4A keys also act like one-shot shifts for the opposite side of the keyboard.
 * The latter behavior is implemented with a prefixing layer.
*/
bool process_prefixing_layers(uint16_t keycode, keyrecord_t *record);

// Adds the One Dead Key to the keys of the 1DK layer
// Also, possibility to apply shift to the key following the dead key :
// when I want to shift a key on the 1DK layer,
// I prefer to press shift then the one-shot key to the 1DK layer than the opposite.
bool insert_1dk(uint16_t keycode);

// Returns whether the 1DK is being sent
bool is_ongoing_1dk(void);