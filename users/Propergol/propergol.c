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


// Mod and layer tap configuration

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
            // Longer tapping term for LT_E, because it’s the only key not covered by Chordal Hold.
            return 300;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
        case LT_SPC:
            // quick tap term to access _SYMBOLS easily after `E` or space
            return 150;
        default:
            return QUICK_TAP_TERM;
    }
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    // No "opposite hands" rule for LT_E
    LAYOUT_split_3x5_3(
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
                // to access _WINMAN with one hand
                return true;
            }
            break;
    }
    // Otherwise defer to the opposite hands rule.
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
            // Disabling Permissive Hold for `E` when the other key is on the same side
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


// Feature configuration

// Numpad/numrow key switch

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
    case M(PG_PLUS):
      return PG_PLUS;
    case LT_AGRV:
      return PG_AGRV;

    default:
      return keycode &= 0xff;
  }
}


static bool number_typed = false;
static bool nav_typed = false;

bool process_macros_I(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {

    switch (keycode) {
      case TG_NUM:
        use_numpad = !use_numpad;
        return false;

        #ifdef KRYPTON_THUMB_SHORTCUTS
      case KC_BSPC:
        if (IS_LAYER_ON(_SHORTNAV) && !nav_typed) { return process_layerword_triggers(NAVWORD, record); }
          //#ifndef KRYPTON_NUMBER_ROW_WITH_ONESHOT
        if (IS_LAYER_ON(_NUMBERS) && !number_typed) { return process_layerword_triggers(NUMWORD, record); }
          //#endif
        break;
        #endif
    }
      //#ifdef KRYPTON_THUMB_SHORTCUTS
    if (IS_LAYER_ON(_NUMBERS)) { number_typed = true; }
    if (IS_LAYER_ON(_SHORTNAV)) { nav_typed = true; }
      //#endif
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
          if (!host_keyboard_led_state().scroll_lock) { tap_code(KC_SCROLL_LOCK); }
          
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

        #ifdef KRYPTON_NUMBER_ROW_WITH_ONESHOT
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

layer_state_t layer_state_set_user(layer_state_t state) {
    if (number_typed && IS_LAYER_OFF_STATE(state, _NUMBERS)) {
        number_typed = false;
    }
    if (nav_typed && IS_LAYER_OFF_STATE(state, _SHORTNAV)) {
        nav_typed = false;
    }
    return state;
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
      case M(PG_PLUS):
        return process_custom_tap_hold(PG_PLUS, record);
      case LT_AGRV:
        return process_custom_tap_hold(PG_AGRV, record);
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


// One-shot on steroids

const oneshot_on_steroids_t oneshot_os[] = {
  {OS(OS_SHFT, OS_SHFT, MOD_BIT(KC_LSFT),                     0      )},
  {OS(OS_WNAV, LT_SPC,  0,                                   _WINMAN )},
  {OS(OS_WNUM, NUM_KEY, MOD_BIT(KC_LGUI),                     0      )},
  {OS(OS_1DK,  OS_1DK,  0,                                   _1DK    )},
  {OS(OS_NUM,  OS_NUM,  0,                                   _NUMBERS)},
  {OS(OS_SYMB, OS_SYMB, 0,                                   _SYMBOLS)},
  {OS(OS_RAS,  OS_RTHB, MOD_BIT(KC_LSFT) | MOD_BIT(KC_ALGR),  0      )}
};

bool is_oneshot_on_steroids_custom_behavior(uint16_t keycode, keyrecord_t* record) {

  if (record->event.pressed) {
    const uint8_t mods = get_mods() | get_oneshot_mods();
    switch (keycode) {

        #ifndef KRYPTON_NUMBER_ROW_WITH_ONESHOT
      case OS_SYMB:
        //const uint8_t mods = get_mods() | get_oneshot_mods();
        if (mods & MOD_MASK_SHIFT) {
          // OS_SYMB when shifted -> oneshot shift + alt-gr
          return process_record_oneshots_on_steroids(OS_RAS, record);
        }
        break;
          #endif

      case OS_1DK:
        // Custom behavior when alt-gr
        //const uint8_t mods = get_mods() | get_oneshot_mods();
        if (mods & MOD_BIT(KC_ALGR)) {
            tap_code16(ALGR(PG_1DK));
            return false;
        }
        break;

        #ifdef KRYPTON_THUMB_SHORTCUTS
      case LT_REPT:
        const int8_t os_shift_state = get_oneshot_on_steroids_state(OS_SHFT);
        if (os_shift_state == 1 || os_shift_state == 3) {
            return toggle_modword(capsword, CAPSWORD, record);
        }
        break;
        #endif
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
    // OS_1DK and OS_NUM shouldn’t deactivate each other
    if (oneshot == OS_1DK && keycode == OS_NUM) { return true; }
    if (oneshot == OS_1DK && keycode == LT_AGRV) { return true; }
    if (oneshot == OS_NUM && keycode == OS_1DK) { return true; }
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
    switch (keycode) {
        case OS_1DK:
          // OS_1DK shouldn’t deactivate other layers
          // for ex. to be combined with _NUMBERS
          return false;
        default:
            return true;
    }
}


// Tap-hold utilities

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

bool process_custom_tap_hold(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {    // On press
      tap_code16(keycode);
      return false;
  }
  return true;
}