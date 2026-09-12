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


#include "kawamashi.h"

  #ifdef IDLE_TIME_BEFORE_HOLD_PRIORITY
static uint16_t next_keycode;
  #endif

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    CHORDAL_HOLD_KAWA_LAYOUT(
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', '*',
                       '*', 'L', '*', '*', 'R', '*'
    );

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

      #ifdef IDLE_TIME_BEFORE_HOLD_PRIORITY
    case LT_MGC:
    case LT_REPT:
      if (get_idle_time() > IDLE_TIME_BEFORE_HOLD_PRIORITY) { return true; }
      return false;
      #else
    case LT_MGC:
      if (next_keycode == OS_WINM) {return true;}
      return false;
    case LT_REPT:
      if (next_keycode == OS_WNUM) {return true;}
      return false;
      #endif

    default:
      return false;
  }
}

bool get_speculative_hold(uint16_t keycode, keyrecord_t* record) {

  // Disable speculative hold during tapping sequences
  if (get_idle_time() < FLOW_TAP_INTERVAL) { return false; }
  // Disable speculative hold when any mods are already active
  // not to mess with hotkeys
  if (get_mods() | get_oneshot_mods()) { return false; }
  
  // Enable speculative holding for these keys.
  if (keycode == I(PG_N)) { return true; }

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

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
        case LT_SPC:
            return 150;
        default:
            return QUICK_TAP_TERM;
    }
}


// Housekeeping

void housekeeping_task_user(void) {
  modword_task();
}


// Key processing

  #ifdef IDLE_TIME_BEFORE_HOLD_PRIORITY
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
      // Cache the next input for mod-tap decisions
      next_keycode = keycode;
  }
  return true;
}
  #endif
  

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


bool on_left_hand(keypos_t pos) {
#ifdef SPLIT_KEYBOARD
  return pos.row < MATRIX_ROWS / 2;
#else
  return (MATRIX_COLS > MATRIX_ROWS) ? pos.col < MATRIX_COLS / 2
                                     : pos.row < MATRIX_ROWS / 2;
#endif
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
    case P(C(PG_A)):
      return C(PG_A);
    case R(C(PG_X)):
      return C(PG_X);
    case M(C(PG_C)) :
      return C(PG_C);
    case I(C(PG_V)):
      return C(PG_V);

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

static bool shift_altgr = false;

void set_shift_altgr(bool target) {
  shift_altgr = target;
}

bool get_shift_altgr(void) {
  return shift_altgr;
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
        if (IS_LAYER_ON(_SYMBOLS)) {
          alt_repeat_key_invoke(&record->event);
        } else {
          repeat_key_invoke(&record->event);
        }
        return false;

      case LT_MGC:
        alt_repeat_key_invoke(&record->event);
        return false;
    }
  } else {
    // Special tap-hold keys (on hold).
    switch (keycode) {

      case LT_SPC:
        if (record->event.pressed) {
          if (get_oneshot_on_steroids_state(OS_SHFT) > 0) {
            cancel_oneshot_on_steroids(OS_SHFT);
            shift_altgr = true;
            return false;
          }
        } else if (shift_altgr) {
          shift_altgr = false;
          return false;
        }
        break;

      case LT_RSA:
        shift_altgr = record->event.pressed;
        return true;
    }
  }
  return true; // Process all other keycodes normally
}


bool process_macros_II(uint16_t keycode, keyrecord_t *record) {

  if (record->tap.count) {
    // Special tap-hold keys (on tap).
    switch (keycode) {
      case P(C(PG_A)):
        return process_custom_tap_hold(C(PG_A), record);
      case R(C(PG_X)):
        return process_custom_tap_hold(C(PG_X), record);
      case M(C(PG_C)) :
        return process_custom_tap_hold(C(PG_C), record);
      case I(C(PG_V)):
        return process_custom_tap_hold(C(PG_V), record);
    }
  }

  if (record->event.pressed) {
    // Other macros (on press).
    switch (keycode) {
      case PG_DEG:
        tap_code(PG_1DK);
        tap_code(KC_0);
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
        case PG_K:
        case PG_B:
        case PG_H:
        case PG_Z:
        case PG_ECIR:
        //case KC_SPC:  // When space is added by clever keys, for ex. in order to uppercase K after '?' for ex.
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
      if (IS_LAYER_ON(_1DK)) {
        switch (keycode) {
          case KC_LEFT:
          case KC_DOWN:
          case KC_RIGHT:
            return keycode;
        }
      }
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
    case C(PG_Z):
      return C(PG_Y);
    case C(PG_Y):
      return C(PG_Z);
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
  {OS(OS_SHFT, OS_SHFT, MOD_BIT(KC_LSFT), _BASE   )},
  {OS(OS_WINM, LT_MGC,  0,                _WINMAN )},
  {OS(OS_WNUM, LT_REPT, MOD_BIT(KC_LGUI), _NUMBERS)},
  {OS(OS_1DK,  OS_1DK,  0,                _1DK    )},
  {OS(OS_NUM,  OS_NUM, 0,                 _NUMBERS)}
};


bool is_oneshot_on_steroids_custom_behavior(uint16_t keycode, keyrecord_t* record) {

  if (!record->event.pressed) { return true; }
  
  switch (keycode) {
      
    case OS_1DK:
      // Custom behavior when alt-gr
      if (shift_altgr) {
        tap_code16(RSA(PG_1DK));
        return false;
      }
      break;

    case LT_PDOT:
      const int8_t os_num_state = get_oneshot_on_steroids_state(OS_NUM);
      if (os_num_state == 3) {
        // OS_NUM + LT_PDOT -> Numword when OS_NUM has not been used yet.
        return process_layerword_triggers(NUMWORD, record);
      }
      break;

    case LT_REPT:
      const int8_t os_shift_state = get_oneshot_on_steroids_state(OS_SHFT);
      if (os_shift_state == 1 || os_shift_state == 3) {
        return toggle_modword(capsword, CAPSWORD, record);
      }
      break;
  }
  return true;
}


bool should_oneshot_on_steroids_ignore_key(uint16_t keycode, uint16_t oneshot, keyrecord_t* record) {

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


bool is_letter(uint16_t keycode) {

  // Taking 1DK layer into account
  if (IS_LAYER_ON(_1DK)) {
    switch (keycode) {

      case PG_V:
      case PG_M:
      case PG_C:
      case PG_X:    // non-breaking hyphen
      case PG_G:    // greek dead key
      case PG_T:    // slash
      case PG_R:    // €
      case PG_L:    // £
      case PG_D:    // umlaut
      case PG_W:    // en dash
        return false;
    }
  }

  switch (keycode) {
    case KC_A ... KC_F:
    case KC_H ... KC_P:
    case KC_R ... KC_S:
    case KC_U ... KC_Z:
    case PG_L:
    case PG_E:
    case PG_F:
    case PG_W:
    case PG_AGRV:
    case PG_EGRV:
    case PG_ECIR:
    case A_CIRC:
    case U_CIRC:
    case LETTER_1DK:
      return true;

    default:
      return false;
  }
}

bool is_send_string_macro(uint16_t keycode) {
  switch (keycode) {
    case N_TILD:
    case MAGIC:
    //case PG_AROB:   // because of Clever Keys
      return true;
    
    default:
      return false;
  }
}

bool is_followed_by_apos(uint16_t keycode, uint16_t prev_keycode) {
  
  switch (keycode) {
    case PG_L:
    case PG_T:
    case PG_D:
    case PG_C:
    case PG_N:
    case PG_S:
    case PG_M:
    case PG_Y:
    case PG_J:
    case PG_I:
      if (is_letter(prev_keycode)) { return false; }
    case PG_Q:
    case PG_U:
      return true;

    default:
      return false;
  }
}


// Mod Word

bool caps_word_press_user(uint16_t keycode) {

  if (IS_LAYER_ON(_1DK)) {
    switch (keycode) {  
      case PG_D:    // umlaut
      case PG_X:    // non-breaking hyphen
      case KC_SPC:  // underscore
        return true;
    }
  }

  // Keycodes that continue Caps Word, with shift applied.
  if (is_letter(keycode) || is_send_string_macro(keycode)) {
    add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
    return true;
  } 

  switch (keycode) {
    // Keycodes that continue Caps Word, without shifting.
    case PG_1DK:
    case PG_TIRE:
    case PG_SLSH:
    case KC_1 ... KC_0:
    case KC_P1 ... KC_P0:
    case KC_BSPC:
    case LCTL(KC_BSPC):
    case KC_DEL:
    case PG_APOS:
      return true;

    default:
      return false;  // Deactivate Caps Word.
    }
}


bool should_continue_caps_list(uint16_t keycode, keyrecord_t* record) {

    // Keycodes that continue Caps List, but not Caps Word.
    // These keycodes trigger the counter to deactivate Caps List.
    switch (keycode) {
      case KC_BSPC:
        return update_capslist_counter(-1);
      case PG_VIRG:
      case KC_SPC:
          return update_capslist_counter(1);
    }

    if (is_letter(keycode) || is_send_string_macro(keycode)) { return update_capslist_counter(1); }

    // This condition can't be merged with the previous one
    // because caps_word_press_user adds shift to letters and send-string macros.
    if (caps_word_press_user(keycode)) { return update_capslist_counter(1); }

    return false;  // Deactivate Caps List.
}


bool list_separator(void) {

    // Words that continue Caps List.
    if (get_recent_keycode(-1) == KC_SPC) {

        if (get_recent_keycode(-2) == PG_VIRG) { return true; }

        if (word_check((uint16_t[]) {KC_SPC, PG_E, PG_T}, 3, 2)) { return true; }

        if (word_check((uint16_t[]) {KC_SPC, PG_O, PG_U}, 3, 2)) { return true; }

        if (word_check((uint16_t[]) {PG_X, PG_C, PG_G}, 3, 2)) { return true; }
    }
    return false;
}

void word_selection_press_user(uint16_t keycode) {

  switch (keycode) {
    case C(KC_LEFT):
        set_nb_word_selected(1);
        tap_code(KC_LEFT);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case C(KC_RGHT):
        set_nb_word_selected(1);
        tap_code(KC_RGHT);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case KC_LEFT:
        select_word(-1);
        set_weak_mods(MOD_BIT_LCTRL | MOD_BIT_LSHIFT);
        break;

    case KC_RIGHT:
        select_word(1);
        set_weak_mods(MOD_BIT_LCTRL | MOD_BIT_LSHIFT);
        break;

    case KC_DOWN:
        select_line(1);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case KC_UP:
        select_line(-1);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case KC_HOME:
    case KC_END:
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case NAVWORD:
        break;

    default:
      disable_modword(selectword);
  }
}


// Keep track of the 1DK, for the Repeat Key
static bool ongoing_1dk = false;

bool process_prefixing_layers(uint16_t keycode, keyrecord_t *record) {

    if (!record->event.pressed) { return true; }    // Nothing special happens on release

    if (ongoing_1dk) {
        if (get_repeat_key_count() > 0) { tap_code(PG_1DK); }
        ongoing_1dk = false;
    }

    // Handling keys and layers related to the One Dead Key (1DK)
    switch (keycode) {
        case PG_1DK:
            return insert_1dk(keycode);
    }

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0) { return true; }
            keycode &= 0xff;
            break;
    }

    if (IS_LAYER_ON(_1DK)) {
        switch (keycode) {
            case PG_K:
            case PG_B:
            case PG_H:
            case PG_Z:
            case PG_Q:
            case PG_APOS:
            case PG_AGRV:
            case PG_ECIR:
            //case KC_SPC:    // When space is added by Clever Keys
                return true;
            case PG_U:
                // handle `quê`
                if (get_recent_keycode(-1) == PG_Q) { return true; }
                
            default:
                return insert_1dk(keycode);
        }
        
    } else if (get_shift_altgr()) {
        if (keycode == PG_N) {
            return insert_1dk(keycode);
        } else {
            set_oneshot_mods(MOD_BIT(KC_RSFT) | MOD_BIT(KC_ALGR));
            return true;
        }
    }
    return true;
}


bool insert_1dk(uint16_t keycode) {

  #ifdef ONE_DEAD_KEY_DEFFERED_SHIFT
    // Special behavior of PG_1DK when shifted
    // Shift must apply to the keycode following PG_1DK.
    const bool shift_mods = get_mods() & MOD_MASK_SHIFT;
    const bool shift_weak_mods = get_weak_mods() & MOD_MASK_SHIFT;
    const bool shift_oneshot_mods = get_oneshot_mods() & MOD_MASK_SHIFT;
    
    if (shift_oneshot_mods) { del_oneshot_mods(MOD_MASK_SHIFT); }
    if (shift_mods) { del_mods(MOD_BIT(KC_LSFT)); }
    if (shift_weak_mods) { del_weak_mods(MOD_MASK_SHIFT); }
  #endif  // ONE_DEAD_KEY_DEFFERED_SHIFT

    ongoing_1dk = true;
    tap_code(PG_1DK);
    
  #ifdef ONE_DEAD_KEY_DEFFERED_SHIFT
    if (shift_oneshot_mods) { set_oneshot_mods(MOD_BIT(KC_LSFT)); }    // Don't use weak mods !
    if (shift_mods) { add_mods(MOD_BIT(KC_LSFT)); }
    if (shift_weak_mods) { add_weak_mods(MOD_BIT(KC_LSFT)); }
  #endif  // ONE_DEAD_KEY_DEFFERED_SHIFT

    return keycode != PG_1DK;
}

bool is_ongoing_1dk(void) {
  return ongoing_1dk;
}