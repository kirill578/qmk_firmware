#include QMK_KEYBOARD_H

#ifdef PS2_MOUSE_ENABLE
    #include "ps2_mouse.h"
    #include "ps2.h"
#endif

#define PRINT LT(0,MEH(KC_F5))
enum layer_names {
    _BASE,
    _BASE2,
    _SYMBOLS,
    _MOUSE,
    _MOUSE_AUTO,
    _ARROW
};

float cutSound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_C3), Q__NOTE(_C1),);
float copySound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_B3),);
float pasteSound[][2] = SONG(Q__NOTE(_B3),);
float undoSound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_A3),);

float leadSound[][2] = SONG(Q__NOTE(_C3), Q__NOTE(_C1), Q__NOTE(_C2), Q__NOTE(_C4),);


// mods
#define      O_GUI    OSM(MOD_LGUI)
#define      O_SFT    OSM(MOD_LSFT)
#define      O_CTL    OSM(MOD_LCTL)
#define      O_ALT    OSM(MOD_LALT)
#define      O_HPR    OSM(MOD_HYPR)
#define      O_MEH    OSM(MOD_MEH)

// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LGUI_T(KC_S)
#define HOME_T LSFT_T(KC_T)
#define HOME_G MEH_T(KC_G)

// Right-hand home row mods
#define HOME_M MEH_T(KC_M)
#define HOME_N RSFT_T(KC_N)
#define HOME_E RGUI_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RCTL_T(KC_O)

// Hold keys
#define COM_SCL LT(0, KC_COMM)
#define DOT_CLN LT(0, KC_DOT)
#define QUO_DQUO LT(0, KC_QUOT)
#define MIN_UND LT(0, KC_MINS)
#define SLS_PIP LT(0, KC_SLSH)


#define HOME_Z LT(0,KC_Z)
#define HOME_X LT(0,KC_X)
#define HOME_C LT(0,KC_C)
#define HOME_D LT(_MOUSE,KC_D)
#define HOME_V LT(0,KC_V)

#define HOME_SPACE LT(_ARROW,KC_SPC)

enum custom_keycodes {
    DEPLOYTEST = SAFE_RANGE,
    INVALIATE,
    RTT_MSE
};
// search str
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool useCMD = false;
    switch (detected_host_os()) {
      case OS_UNSURE:
        useCMD = true;
        break;
      case OS_MACOS:
      case OS_IOS:
        useCMD = true;
        break;
      default:
        break;
    }
    mod_state = get_mods();
    switch (keycode) {
        case KC_BSPC:
            {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
        }
        case LT(_MOUSE,KC_D):
            if (record->event.pressed) {
                ps2_set_multiplier(6);
            } else {
                ps2_set_multiplier(2);
            }
            return true;
        case KC_ACL0:
            if (record->event.pressed) {
                ps2_set_multiplier(1);  // todo make it more reliable
            }
            return true;
        case KC_LEFT:
            {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool key_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_CTRL && mod_state & MOD_MASK_SHIFT && mod_state & MOD_MASK_ALT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_CSA);
                    register_code(KC_MS_BTN4);
                    // Update the boolean variable to reflect the status of KC_DEL
                    key_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (key_registered) {
                    unregister_code(KC_MS_BTN4);
                    key_registered = false;
                    return false;
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
        }
        case KC_RIGHT:
            {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool key_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_CTRL && mod_state & MOD_MASK_SHIFT && mod_state & MOD_MASK_ALT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_CSA);
                    register_code(KC_MS_BTN5);
                    // Update the boolean variable to reflect the status of KC_DEL
                    key_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (key_registered) {
                    unregister_code(KC_MS_BTN5);
                    key_registered = false;
                    return false;
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
        }
        case RTT_MSE: {
            uint16_t static x = 1;
            if (record->event.pressed) {
                if (x % 3 == 0) {
                    tap_code16(C(A(S(KC_F1))));
                } else if (x % 3 == 1) {
                    tap_code16(C(A(S(KC_F2))));
                } else if (x % 3 == 2) {
                    tap_code16(C(A(S(KC_F3))));
                }
            }
            x++;
            break;
        }
        case LT(0,KC_X):
            if (!record->tap.count && record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(cutSound);
                #endif //AUDIO_ENABLE
                tap_code16(useCMD ? G(KC_X) : C(KC_X));
                return false;
            }
            return true;
        case LT(0,KC_C):
            if (!record->tap.count && record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(copySound);
                #endif //AUDIO_ENABLE
                tap_code16(useCMD ? G(KC_C) : C(KC_C));
                return false;
            }
            return true;
        case LT(0,KC_V):
            if (!record->tap.count && record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(pasteSound);
                #endif //AUDIO_ENABLE
                tap_code16(useCMD ? G(KC_V) : C(KC_V));
                return false;
            }
            return true;
        case LT(0,KC_Z):
            if (!record->tap.count && record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(undoSound);
                #endif //AUDIO_ENABLE
                tap_code16(useCMD ? G(KC_Z) : C(KC_Z));
                return false;
            }
            return true;
        case LT(0,KC_QUOT):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_GRV);
                return false;
            }
            return true;
        case LT(0,KC_SLSH):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_EXLM);
                return false;
            }
            return true;
        case LT(0,KC_AMPR):
            if (!record->tap.count && record->event.pressed) {
                SEND_STRING("|");
                return false;
            }
            if (record->tap.count && record->event.pressed) {
                SEND_STRING("&");
                return false;
            }
            return true;
        case KC_P0:
        case KC_P1:
        case KC_P2:
        case KC_P3:
        case RSFT_T(KC_P4):
        case RGUI_T(KC_P5):
        case LALT_T(KC_P6):
        case KC_P7:
        case KC_P8:
        case KC_P9:
            if (!host_keyboard_led_state().num_lock && !useCMD) {
                tap_code(KC_NUM_LOCK);
            }
            return true;
    }
    return true;
}

static uint16_t trackpoint_timer;
extern int tp_buttons;

void ps2_mouse_moved_user(report_mouse_t *mouse_report) { // Whenever the TrackPoint starts moving, check if the timer exists.
    if (trackpoint_timer) {
        trackpoint_timer = timer_read();
    } else {
        if (!tp_buttons) { //I'm still a bit confused about this one, but I believe it checks that if the mousekey state isn't set, turn on this layer specified?
            layer_on(_MOUSE_AUTO);
            trackpoint_timer = timer_read();
        }

    }
}

void matrix_scan_user(void) {  // ALWAYS RUNNING VOID FUNCTION, CAN BE USED TO CHECK CLOCK RUNTIMES OVER THE DURATION THAT THE KEYBOARD IS POWERED ON
  if (trackpoint_timer && (timer_elapsed(trackpoint_timer) > 750)) { //If the time of both the TP timer
    if (!tp_buttons) {
      layer_off(_MOUSE_AUTO);
      trackpoint_timer = 0; //Reset the timer again until the mouse moves more
    }
  }
}

enum combos {
    TN_CW_TOGGLE,
    ST_OP,
    NE_CP,
    NI_DEL,
    GM_LEAD,
    _46_DEL,
    FP_OC,
    LU_CC,
    COMMA_DOT_MINUS,
    QW_ESC,
    CD_LBRC,
    HCOMMA_RBRC,
    YOU_COMBO,
    EI_ENTER,

    AT_V,
    HASH_V,
    DOLLAR_V,
    PERCENT_V,

    CARET_V,
    PLUS_V,
    AST_V,
    AMP_V,

    // placeholder  here
    BSLS_V,
    EQUAL_V,
    TILD_V,

    UNDS_V,
    MIN_V,
    SLSH_V,
    PIPE_V,

    WORD_BSPC
};

const uint16_t PROGMEM tn_cw_toggle[] = {HOME_T, HOME_N, COMBO_END};
const uint16_t PROGMEM st_op[] = {HOME_S, HOME_T, COMBO_END};
const uint16_t PROGMEM ne_cp[] = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM ni_del[] = {HOME_N, HOME_I, COMBO_END};
const uint16_t PROGMEM gm_lead[] = {HOME_G, HOME_M, COMBO_END};
const uint16_t PROGMEM _46_del[] = {RSFT_T(KC_P4), LALT_T(KC_P6), COMBO_END};
const uint16_t PROGMEM fp_oc[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lu_cc[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM comma_dot_minus[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM qw_esc[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM cd_lbrc[] = {LT(0,KC_C), LT(_MOUSE,KC_D), COMBO_END};
const uint16_t PROGMEM hcomma_rbrc[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM you_combo[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM ei_enter[] = {HOME_E, HOME_I, COMBO_END};

const uint16_t PROGMEM at_v[] = {KC_W, HOME_R, COMBO_END};
const uint16_t PROGMEM hash_v[] = {KC_F, HOME_S, COMBO_END};
const uint16_t PROGMEM dollar_v[] = {KC_P, HOME_T, COMBO_END};
const uint16_t PROGMEM percent_v[] = {KC_B, HOME_G, COMBO_END};

const uint16_t PROGMEM caret_v[] = {KC_J, HOME_M, COMBO_END};
const uint16_t PROGMEM plus_v[] = {KC_L, HOME_N, COMBO_END};
const uint16_t PROGMEM ast_v[] = {KC_U, HOME_E, COMBO_END};
const uint16_t PROGMEM amp_v[] = {KC_Y, HOME_I, COMBO_END};

// placeholder  here
const uint16_t PROGMEM bsls_v[] = {HOME_S, HOME_C, COMBO_END};
const uint16_t PROGMEM equal_v[] = {HOME_T, HOME_D, COMBO_END};
const uint16_t PROGMEM tild_v[] = {HOME_G, HOME_V, COMBO_END};

const uint16_t PROGMEM unds_v[] = {HOME_M, KC_K, COMBO_END};
const uint16_t PROGMEM min_v[] = {HOME_N, KC_H, COMBO_END};
const uint16_t PROGMEM slsh_v[] = {HOME_E, KC_COMM, COMBO_END};
const uint16_t PROGMEM pipe_v[] = {HOME_I, KC_DOT, COMBO_END};

const uint16_t PROGMEM word_bspc[] = {HOME_SPACE, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
    [TN_CW_TOGGLE] = COMBO(tn_cw_toggle, CW_TOGG),
    [ST_OP] = COMBO(st_op, S(KC_9)),
    [NE_CP] = COMBO(ne_cp, S(KC_0)),
    [NI_DEL] = COMBO(ni_del, KC_DEL),
    [GM_LEAD] = COMBO(gm_lead, QK_LEAD),
    [_46_DEL] = COMBO(_46_del, KC_DEL),
    [FP_OC] = COMBO(fp_oc, KC_LCBR),
    [LU_CC] = COMBO(lu_cc, KC_RCBR),
    [COMMA_DOT_MINUS] = COMBO(comma_dot_minus, KC_MINS),
    [QW_ESC] = COMBO(qw_esc, KC_ESC),
    [CD_LBRC] = COMBO(cd_lbrc, KC_LBRC),
    [HCOMMA_RBRC] = COMBO(hcomma_rbrc, KC_RBRC),
    [EI_ENTER] = COMBO(ei_enter, KC_ENTER),
    [YOU_COMBO] = COMBO_ACTION(you_combo),

    [AT_V] =  COMBO(at_v, KC_AT),
    [HASH_V] =  COMBO(hash_v, KC_HASH),
    [DOLLAR_V] =  COMBO(dollar_v, KC_DLR),
    [PERCENT_V] =  COMBO(percent_v, KC_PERC),

    [CARET_V] =  COMBO(caret_v, KC_CIRC),
    [PLUS_V] =  COMBO(plus_v, KC_PLUS),
    [AST_V] =  COMBO(ast_v, KC_ASTR),
    [AMP_V] =  COMBO(amp_v, KC_AMPR),

    // placeholder  here
    [BSLS_V] =  COMBO(bsls_v, KC_BSLS),
    [EQUAL_V] =  COMBO(equal_v, KC_EQL),
    [TILD_V] =  COMBO(tild_v, KC_TILD),

    [UNDS_V] =  COMBO(unds_v, KC_UNDS),
    [MIN_V] =  COMBO(min_v, KC_MINS),
    [SLSH_V] =  COMBO(slsh_v, KC_SLSH),
    [PIPE_V] =  COMBO(pipe_v, KC_PIPE),

    [WORD_BSPC] = COMBO_ACTION(word_bspc)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  bool useCMD = false;
  switch (detected_host_os()) {
      case OS_UNSURE:
        useCMD = true;
        break;
      case OS_MACOS:
      case OS_IOS:
        useCMD = true;
        break;
      default:
        break;
  }
  mod_state = get_mods();
  switch(combo_index) {
    case YOU_COMBO:
      if (pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
          SEND_STRING("You");
        } else {
          SEND_STRING("you");
        }
      }
      break;
     case WORD_BSPC:
        if (pressed) {
            tap_code16(useCMD ? A(KC_BSPC) : C(KC_BSPC));
        }
  }
}

void leader_start_user(void) {
    #ifdef AUDIO_ENABLE
        PLAY_SONG(leadSound);
    #endif //AUDIO_ENABLE
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_A, KC_F)) {
        SEND_STRING("() => {}");
        tap_code16(KC_LEFT);
        tap_code16(KC_ENTER);
        tap_code16(KC_TAB);
    } else if (leader_sequence_two_keys(KC_F, KC_N)) {
        SEND_STRING("function() {}");
        tap_code16(KC_LEFT);
        tap_code16(KC_ENTER);
        tap_code16(KC_TAB);
    } else if (leader_sequence_four_keys(KC_D, KC_E, KC_P, KC_L)) {
        SEND_STRING("yarn build:test && yarn deploy:test\n");
    } else if (leader_sequence_four_keys(KC_I, KC_N, KC_V, KC_A)) {
        SEND_STRING("yarn invalidate-cache:test\n");
    } else if (leader_sequence_four_keys(KC_S, KC_C, KC_A, KC_P)) {
        tap_code16(G(S(KC_4)));
    } else if (leader_sequence_four_keys(KC_B, KC_O, KC_O, KC_T)) {
        reset_keyboard();
    }
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,        KC_W,       KC_F,            KC_P,               KC_B,                               KC_J,    KC_L,       KC_U,         KC_Y,   LT(0,KC_QUOT),
      HOME_A,      HOME_R,     HOME_S,          HOME_T,             HOME_G,                             HOME_M,  HOME_N,     HOME_E,       HOME_I,          HOME_O,
      HOME_Z,      HOME_X,     HOME_C,          HOME_D,             HOME_V,                               KC_K,    KC_H,    KC_COMM,       KC_DOT,         KC_QUES,
                  KC_LEFT,   KC_RIGHT,          KC_TAB,         HOME_SPACE,                            KC_BSPC, LT(_SYMBOLS,KC_ENT), LT(0,KC_AMPR),  KC_SCLN
    ),
    [_SYMBOLS] = LAYOUT(
        KC_CIRC,     KC_F7,    KC_F8,   KC_F9,  KC_F10,                              KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_AT,       KC_F4,    KC_F5,   KC_F6,  KC_F11,                              KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_HASH,     KC_F1,    KC_F2,   KC_F3,  KC_F12,                              KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_LPRN, KC_RPRN
    ),
    [_MOUSE]      = LAYOUT(
        _______,     _______,    _______,    _______,    _______,                    KC_WH_L,    KC_WH_D,    KC_MS_U,  KC_WH_U,   KC_WH_R,
        _______,     _______,    _______,    _______,    _______,                    _______,    KC_MS_L,    KC_MS_D,  KC_MS_R,    KC_F12,
        _______,     KC_ACL2,    KC_ACL0,    KC_TRNS,    _______,                    _______,    _______,    RTT_MSE,   _______,  _______,
                     KC_BTN4,     KC_BTN5,   _______,   KC_BTN3,                     KC_BTN1,    KC_BTN2,    KC_WH_D,  KC_WH_U
    ),
    [_MOUSE_AUTO]      = LAYOUT( // have to duplicate to avoid the manual activation of layer from timing outt
        _______,     _______,    _______,    _______,    _______,                    _______, _______,    _______,  _______,    _______,
        _______,     _______,    _______,    _______,    _______,                    _______, _______,    _______,  _______,    _______,
        _______,     _______,    _______,    _______,    _______,                    _______, _______,    RTT_MSE,  _______,    _______,
                    KC_BTN4,     KC_BTN5,    _______,   _______,                     KC_BTN1, KC_BTN2,    KC_WH_D,  KC_WH_U
    ),
    [_ARROW]      = LAYOUT(
       KC_NO,        KC_NO,    KC_UP,      KC_NO,   KC_NO,                               KC_PEQL,         KC_P7,          KC_P8,         KC_P9,  KC_DLR,
     KC_HOME,      KC_LEFT,  KC_DOWN,    KC_RGHT,  KC_END,                               KC_PPLS,  RSFT_T(KC_P4),  RGUI_T(KC_P5), LALT_T(KC_P6), KC_PERC,
        KC_Z,   KC_MS_BTN4,     KC_C, KC_MS_BTN5,    KC_V,                               KC_ASTR,         KC_P1,          KC_P2,         KC_P3,  KC_PEQL,
                    KC_BTN4, KC_BTN5,     KC_TAB,  KC_SPC,                               KC_TRNS, KC_P0, KC_BSLS, KC_PDOT
    )
};


#ifdef PS2_MOUSE_ENABLE
void ps2_mouse_init_user() {
    uint8_t rcv;

    // see p24 https://blogs.epfl.ch/icenet/documents/Ykt3Eext.pdf

    // set TrackPoint sensitivity
    PS2_MOUSE_SEND(0xE2, "tpsens: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpsens: 0x81");
    PS2_MOUSE_SEND(0x4A, "tpsens: 0x4A");
    PS2_MOUSE_SEND(0x49, "tpsens: 0x68");

    // set TrackPoint Negative Inertia factor
    PS2_MOUSE_SEND(0xE2, "tpnegin: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpnegin: 0x81");
    PS2_MOUSE_SEND(0x4D, "tpnegin: 0x4D");
    PS2_MOUSE_SEND(0x06, "tpnegin: 0x06");

    // set TrackPoint speed
    // (transfer function upper plateau speed)
    PS2_MOUSE_SEND(0xE2, "tpsp: 0xE2");
    PS2_MOUSE_SEND(0x81, "tpsp: 0x81");
    PS2_MOUSE_SEND(0x60, "tpsp: 0x60");
    PS2_MOUSE_SEND(0x61, "tpsp: 0xAA");

    // inquire pts status
    rcv = ps2_host_send(0xE2);
    rcv = ps2_host_send(0x2C);
    rcv = ps2_host_recv_response();
    if ((rcv & 1) == 1) {
    // if on, disable pts
    rcv = ps2_host_send(0xE2);
    rcv = ps2_host_send(0x47);
    rcv = ps2_host_send(0x2C);
    rcv = ps2_host_send(0x01);
    }

}
#endif


// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   k e y   o v e r r i d e s         │
// └─────────────────────────────────────────────────┘

// shift + ? = !
const key_override_t quexclam_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);

// Override comma key: no mod = , | shift = ; | ctrl+shift = <
const key_override_t semicolon_override =
  ko_make_with_layers_negmods_and_options(
      MOD_MASK_SHIFT,       // Trigger modifiers: shift
      KC_COMM,             // Trigger key: meh_comma hold tap key
      KC_SCLN,             // Replacement key: ;
      ~0,                  // Activate on all layers
      MOD_MASK_CA,         // Do not activate when ctrl, alt or gui is pressed
      ko_option_no_reregister_trigger);
const key_override_t lt_override =
  ko_make_with_layers_negmods_and_options(
    MOD_MASK_CS,      // Trigger modifiers: ctrl+shift
    KC_COMM,         // Trigger key: meh_comma hold tap key
    KC_LT,         // Replacemeng key: <
    ~0,              // All layers
    MOD_MASK_AG,     // Do not activate when alt or gui is pressed
    ko_option_no_reregister_trigger);

// Override . key: no mod = . | shift = : | ctrl+shift = >
const key_override_t colon_override =
  ko_make_with_layers_negmods_and_options(
      MOD_MASK_SHIFT,      // Trigger modifiers: shift
      KC_DOT,              // Trigger key: dot key
      KC_COLN,             // Replacement key: :
      ~0,                  // Activate on all layers
      MOD_MASK_CA,        // Do not activate when ctrl or alt is pressed
      ko_option_no_reregister_trigger);
const key_override_t gt_override =
  ko_make_with_layers_negmods_and_options(
    MOD_MASK_CS,           // Trigger modifiers: ctrl+shift
    KC_DOT,                // Trigger key: dot key
    KC_GT,                 // Replacemeng key: >
    ~0,                    // All layers
    MOD_MASK_AG,           // Do not activate when alt or gui is pressed
    ko_option_no_reregister_trigger);

// This globally defines all key overrides to be used ├───────────┐
const key_override_t **key_overrides = (const key_override_t *[]){
  &quexclam_override,
  &semicolon_override,
  &lt_override,
  &colon_override,
  &gt_override,
  NULL // Null terminate the array of overrides!
};
