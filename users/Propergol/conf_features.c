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

bool on_left_hand(keypos_t pos) {
#ifdef SPLIT_KEYBOARD
  return pos.row < MATRIX_ROWS / 2;
#else
  return (MATRIX_COLS > MATRIX_ROWS) ? pos.col < MATRIX_COLS / 2
                                     : pos.row < MATRIX_ROWS / 2;
#endif
}

bool bilateral_combination(const keyrecord_t* tap_hold_record, const keyrecord_t* other_record) {
  return on_left_hand(tap_hold_record->event.key) != on_left_hand(other_record->event.key);
}

// By default, use the BILATERAL_COMBINATIONS rule to consider the tap-hold key
// "held" only when it and the other key are on opposite hands.
__attribute__((weak)) bool approved_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                                           uint16_t other_keycode, keyrecord_t* other_record) {
  return bilateral_combination(tap_hold_record, other_record);
}

static bool use_numpad = false;

void set_use_numpad(bool target) {
  use_numpad = target;
}

bool should_use_numpad(void) {
  return use_numpad;
}


uint16_t tap_hold_extractor(uint16_t keycode) {

  switch (keycode) {
/*     case MOD_STB:
      return S(KC_TAB); */
    case M(BACKWRD):
      return BACKWRD;
    case P(PG_ASTX):
      return PG_ASTX;
    case R(PG_PLUS):
      return PG_PLUS;

    default:
      return keycode &= 0xff;
  }
}

bool process_custom_tap_hold(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {    // On press
      tap_code16(keycode);
      return false;
  }
  return true;
}

bool process_macros_I(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
    switch (keycode) {

      case TG_NUM:
        use_numpad = !use_numpad;
        return false;
    }
  }

  if (record->tap.count) {
    // Special tap-hold keys (on tap).
    switch (keycode) {
      case LT_REPT:
        repeat_key_invoke(&record->event);
        return false;

      case LT_MGC:
        alt_repeat_key_invoke(&record->event);
        return false;

      case PANIC:
        if (record->event.pressed) {
          if (!host_keyboard_led_state().num_lock) { tap_code(KC_NUM_LOCK); }
          
          if (get_layerword_layer() != 0) { disable_layerword(get_layerword_layer()); }
          layer_clear();
          use_numpad = false;
          unregister_code(KC_LCTL);
          unregister_code(KC_LSFT);
          unregister_code(KC_LALT);
          unregister_code(KC_LGUI);
          //clear_weak_mods();
          if (get_modword() != idle) { disable_modword(get_modword()); }
          clear_recent_keys();
        }
        return false;
    }
  } else {
    switch (keycode) {
        #ifdef KRYPTON_ONESHOT_NUMBERS
      case LT_REPT:
        if (record->event.pressed) {
          if (get_oneshot_on_steroids_state(OS_SHFT) > 0) {
            cancel_oneshot_on_steroids(OS_SHFT);
            register_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_ALGR));
            return false;
          }
        } else {
          if (get_mods() & MOD_BIT(KC_ALGR)) {
            unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_ALGR));
            return false;
          }
        }
        break;
        #endif
    }
  }
  return true; // Process all other keycodes normally
}


bool process_macros_II(uint16_t keycode, keyrecord_t *record) {

  if (record->tap.count) {
    // Special tap-hold keys (on tap).
    switch (keycode) {
/*       case MOD_STB:
        return process_custom_tap_hold(S(KC_TAB), record); */
      case M(BACKWRD):
        return process_custom_tap_hold(BACKWRD, record);
      case P(PG_ASTX):
        return process_custom_tap_hold(PG_ASTX, record);
      case R(PG_PLUS):
        return process_custom_tap_hold(PG_PLUS, record);
    }
  }

  if (record->event.pressed) {
    // Other macros (on press).
    switch (keycode) {
      case PG_DEG:
        tap_code(PG_1DK);
        tap_code(KC_0);
        return false;
      case HOME:
          #ifdef KRYPTON_MAC_MODIFIERS
        tap_code16(LCMD(KC_LEFT));
          #else
        tap_code(KC_HOME);
          #endif
        return false;
      case END:
          #ifdef KRYPTON_MAC_MODIFIERS
        tap_code16(LCMD(KC_RIGHT));
          #else
        tap_code(KC_END);
          #endif
        return false;
    }
  }
  return true; // Process all other keycodes normally
}


// Clever keys configuration

uint16_t get_ongoing_keycode_user(uint16_t keycode, keyrecord_t* record) {
  // Handles custom keycodes to be processed for Clever Keys

  if (is_send_string_macro(keycode)) { return keycode; }

  if (keycode == KC_BSPC) {
    // Setting the key to be repeated to match the key buffer.
    if (is_followed_by_apos(get_recent_keycode(-1), get_recent_keycode(-2))) {
        set_last_keycode(PG_APOS);
    } else {
        set_last_keycode(get_recent_keycode(-1));
    }
    return KC_NO;
  }

  switch (get_highest_layer(layer_state)) {

    case _1DK:
      switch (keycode) {
        case PG_Z:
        case PG_ECIR:
          return keycode;

        case PG_POIN:
          return PG_3PTS;
        case PG_U:
          return U_CIRC;
        case PG_A:
          return A_CIRC;

        default:
          if (is_letter(keycode)) { return LETTER_1DK; }
          return SYMBOL_1DK;
      }
    
    // There are no symbols on _SHORTNAV, _WINMAN or _FUNCTIONS
    case _SHORTNAV:
    case _WINMAN:
    case _FUNCTIONS:
      clear_recent_keys();
      return KC_NO;
  }

  switch (keycode) {
    case PG_E:    // because PG_E is not a basic keycode
      return keycode;
  }

  // Handles combos
  if (!IS_KEYEVENT(record->event)) {
    switch (keycode) {
      case KC_BSPC:
        return KC_TRNS;

      default:
        clear_recent_keys();
        return KC_NO;
    }
  }
  return KC_TRNS;
}


// Repeat and Magic keys

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {

  // Custom oneshots don't type anything on their own. They mustn't be remembered.
  if (is_oneshot_on_steroids(keycode)) { return false; }

  if (is_letter(tap_hold_extractor(keycode))) {
    // Forget Shift on letter keys when Shift or AltGr are the only mods.
    if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
      *remembered_mods &= ~MOD_MASK_SHIFT;
      return true;
    }
  }

  switch (keycode) {
    case KC_BSPC:
    case LT_REPT:
    case LT_MGC:
      return false;
    
    default:
      return true;
  }
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {

  if (get_last_keycode() == KC_NO) { return MAGIC; }

  switch (keycode) {
    case UNDO:
      return REDO;
    case REDO:
      return UNDO;
  }

  if (mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_ALGR))) {
    // regular behaviour of the alt-repeat key when a modifier
    // other than shift or alt-gr is registered
    return KC_TRNS;
  }

  keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
  switch (keycode) {
    // regular behaviour of the alt-repeat key for these keycodes
    case KC_LEFT:
    case KC_RIGHT:
    case KC_DOWN:
    case KC_UP:
    case KC_PGUP:
    case KC_PGDN:
    case KC_HOME:
    case KC_END:
      return KC_TRNS;
  }
  return MAGIC;
}


// One-shot mods

const oneshot_on_steroids_t oneshot_os[] = {
  {OS(OS_SHFT, OS_SHFT, MOD_BIT(KC_LSFT),                     0      )},
  {OS(OS_WNAV, LT_SPC,  0,                                   _WINMAN )},
  {OS(OS_WNUM, NUM_KEY, MOD_BIT(KC_LGUI),                     0      )},
  //{OS(OS_WPAD, LT_MGC,  MOD_BIT(KC_LGUI),                     0      )},
  {OS(OS_1DK,  OS_1DK,  0,                                   _1DK    )},
  //{OS(OS_NUMR, OS_NUMR, 0,                                   _NUMBERS)},
  {OS(OS_NUM,  OS_NUM,  0,                                   _NUMBERS)},
  //{OS(OS_SYMB, OS_SYMB, 0,                                   _SYMBOLS)},
  {OS(OS_RTHB, OS_RTHB, 0,                                   _OS_LAYR)},
  {OS(OS_RAS,  OS_RTHB, MOD_BIT(KC_LSFT) | MOD_BIT(KC_ALGR),  0      )}
};

bool is_oneshot_on_steroids_custom_behavior(uint16_t keycode, keyrecord_t* record) {

  if (record->event.pressed) {
    switch (keycode) {

      case OS_RTHB:
          #ifdef KRYPTON_ONESHOT_NUMBERS
        if (IS_LAYER_ON(_1DK)) {
          insert_1dk(keycode);
        } else if (get_oneshot_on_steroids_state(OS_SHFT) > 0) {
          // OS_SHFT + OS_NUM -> Capsword only if layer _1DK is off.
          // On _1DK layer, OS_NUM can be combined with shift to tap symbols like ⅔, ¾ etc.
          return toggle_modword(capsword, CAPSWORD, record);
        }
          #else
        if (get_oneshot_on_steroids_state(OS_SHFT) > 0) {
          // OS_SHFT + OS_SYMB -> oneshot shift + alt-gr
          return process_record_oneshots_on_steroids(OS_RAS, record);
        }
          #endif
        break;

        #ifdef KRYPTON_ONESHOT_NUMBERS
      case OS_SHFT:
        const int8_t os_num_state = get_oneshot_on_steroids_state(OS_RTHB);
        if (os_num_state == 1 || os_num_state == 3) {
          // OS_NUMR + OS_SHFT -> Numword when OS_NUMR has not been used yet.
          return process_layerword_triggers(NUMWORD, record);
        }
        break;
        #endif

      case OS_1DK:
        // Custom behavior when alt-gr
        const uint8_t mods = get_mods() | get_oneshot_mods();
        if (mods & MOD_BIT(KC_ALGR)) {
            tap_code16(ALGR(PG_1DK));
            return false;
        }
        break;
    }
  }
  return true;
}

bool is_oneshot_on_steroids_cancel_key(uint16_t keycode) {
    switch (keycode) {
      case PANIC:
        return true;
      default:
        return false;
    }
}

bool should_oneshot_on_steroids_ignore_key(uint16_t keycode, uint16_t oneshot, keyrecord_t* record) {

  const uint8_t mods = get_mods() | get_oneshot_mods();
  if (keycode == OS_1DK && (mods & MOD_BIT(KC_ALGR))) { return false; }

  bool is_mod_key = is_oneshot_mod_on_steroids(keycode);
  bool is_layer_key = is_oneshot_layer_on_steroids(keycode);
  
  if (!record->tap.count) {
    if (IS_QK_MOD_TAP(keycode)) { is_mod_key = true; }
    if (IS_QK_LAYER_TAP(keycode)) { is_layer_key = true; }
  }

  if (!is_mod_key && !is_layer_key) { return false; }

  // Mod or layer-change key pressed after an OSoS key
  if (is_oneshot_layer_on_steroids(oneshot)) {
    // If a layer-change key is pressed after a OSL, the OSL must be reset.
    if (is_layer_key) { return false; }
    // keycode is not a layer key, it’s a mod key.
#     ifdef OS_MOD_SHOULD_LEAVE_OS_LAYER
    // When using OSM as Callum mods, an OSL tapped before must be reset.
    if (is_oneshot_mod_on_steroids(keycode)) { return false; }
#     endif  // OS_MOD_SHOULD_LEAVE_OS_LAYER
    // Standard behavior, like any mod key after an OSL
    return true;
  } else {
    // one-shot is OSM on steroids
#     ifdef OS_STEROIDS_ABSORB_MODS
    if (is_oneshot_layer_on_steroids(keycode)) {
        if (should_oneshot_on_steroids_absorb_mods(keycode)) { return false; }
    }
#     endif  // OS_STEROIDS_ABSORB_MODS
    // OSM on steroids should stay pressed
    // whether keycode is a mod or a layer-change key.
    return true;
  }
}

bool should_oneshot_on_steroids_deactivate_layer(uint16_t keycode, uint8_t layer) {
/*   switch (keycode) {
    case OS_NUMR:
    case OS_WROW:
      return true;

    default:
      return false;
  } */
  return true;
}