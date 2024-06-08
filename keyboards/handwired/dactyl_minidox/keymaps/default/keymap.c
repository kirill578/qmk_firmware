#include QMK_KEYBOARD_H

#ifdef PS2_MOUSE_ENABLE
    #include "ps2_mouse.h"
    #include "ps2.h"
#endif

enum layer_names {
    _BASE,
    _SYMBOLS,
    _MOUSE,
    _MOUSE_AUTO,
    _MOUSE_AUTO2,
    _ARROW,
    _GAME,
    _GAME2,
};

#ifdef AUDIO_ENABLE
float cutSound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_C3), Q__NOTE(_C1),);
float copySound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_B3),);
float pasteSound[][2] = SONG(Q__NOTE(_B3),);
float undoSound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_A3),);

float leadSound[][2] = SONG(Q__NOTE(_C3), Q__NOTE(_C1), Q__NOTE(_C2), Q__NOTE(_C4),);
float mehSound[][2] = SONG(Q__NOTE(_C3));
float mehOffSound[][2] = SONG(Q__NOTE(_C3), Q__NOTE(_C1),);
#endif //AUDIO_ENABLE

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
    RTT_MSE,
    WR_BSPC,
    PRINT,
    PRINT_CP,
    PRINT_VID,
    LT_SYM_OSM_MEH,
    DRAG_SCROLL
};

bool set_scrolling = false;

// search str
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == DRAG_SCROLL && record->event.pressed) {
        set_scrolling = !set_scrolling;
    }
    bool useCMD = detected_host_os() == OS_MACOS;
    mod_state = get_mods();
    switch (keycode) {
        case LT_SYM_OSM_MEH: {
            static uint16_t key_timer;
            if (record->event.pressed) {
                key_timer = timer_read();
                layer_on(_SYMBOLS);
            } else {
                layer_off(_SYMBOLS);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    if (!get_oneshot_mods()) {
                        #ifdef AUDIO_ENABLE
                            PLAY_SONG(mehSound);
                        #endif //AUDIO_ENABLE
                        add_weak_mods(MOD_MEH);
                        set_oneshot_mods(MOD_MEH);
                    } else {
                        #ifdef AUDIO_ENABLE
                            PLAY_SONG(mehOffSound);
                        #endif //AUDIO_ENABLE
                        clear_oneshot_mods();
                    }
                }
            }
            return false; // Skip all further processing of this key
        }
        case PRINT:
            if (record->event.pressed) {
                tap_code16(useCMD ? S(G(KC_4)) : S(G(KC_S)));
            }
            return false;
        case PRINT_CP:
            if (record->event.pressed) {
                tap_code16(useCMD ? S(G(C(KC_4))) : S(G(KC_C)));
            }
            return false;
        case PRINT_VID:
            if (record->event.pressed) {
                tap_code16(useCMD ? S(G(KC_5)) : S(G(KC_S)));
            }
            return false;
        case WR_BSPC:
            if (record->event.pressed) {
                tap_code16(useCMD ? A(KC_BSPC) : C(KC_BSPC));
            }
            return false;
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
    _46_DEL,
    FP_OC,
    LU_CC,
    COMMA_DOT_MINUS,
    WF_ESC,
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

    WORD_BSPC,

    RT_TAB,
    RST_STAB,
};

const uint16_t PROGMEM tn_cw_toggle[] = {HOME_T, HOME_N, COMBO_END};
const uint16_t PROGMEM st_op[] = {HOME_S, HOME_T, COMBO_END};
const uint16_t PROGMEM ne_cp[] = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM ni_del[] = {HOME_N, HOME_I, COMBO_END};
const uint16_t PROGMEM _46_del[] = {RSFT_T(KC_P4), LALT_T(KC_P6), COMBO_END};
const uint16_t PROGMEM fp_oc[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lu_cc[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM comma_dot_minus[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM wf_esc[] = {KC_W, KC_F, COMBO_END};
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

const uint16_t PROGMEM reset_tab[] = {HOME_R, HOME_T, COMBO_END};
const uint16_t PROGMEM reset_stab[] = {HOME_R, HOME_S, HOME_T, COMBO_END};


combo_t key_combos[] = {
    [TN_CW_TOGGLE] = COMBO(tn_cw_toggle, CW_TOGG),
    [ST_OP] = COMBO(st_op, S(KC_9)),
    [NE_CP] = COMBO(ne_cp, S(KC_0)),
    [NI_DEL] = COMBO(ni_del, KC_DEL),
    [_46_DEL] = COMBO(_46_del, KC_DEL),
    [FP_OC] = COMBO(fp_oc, KC_LCBR),
    [LU_CC] = COMBO(lu_cc, KC_RCBR),
    [COMMA_DOT_MINUS] = COMBO(comma_dot_minus, KC_MINS),
    [WF_ESC] = COMBO(wf_esc, KC_ESC),
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

    [WORD_BSPC] = COMBO_ACTION(word_bspc),

    [RT_TAB] = COMBO(reset_tab, KC_TAB),
    [RST_STAB] = COMBO(reset_stab, S(KC_TAB)),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (get_highest_layer(default_layer_state)) {
        case _GAME:
            if (combo_index == WF_ESC) {
                return true;
            }
            return false;
    }
    return true;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  bool useCMD = detected_host_os() == OS_MACOS;
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,        KC_W,       KC_F,            KC_P,               KC_B,                               KC_J,    KC_L,       KC_U,         KC_Y,   LT(0,KC_QUOT),
      HOME_A,      HOME_R,     HOME_S,          HOME_T,             HOME_G,                             HOME_M,  HOME_N,     HOME_E,       HOME_I,          HOME_O,
      HOME_Z,      HOME_X,     HOME_C,          HOME_D,             HOME_V,                               KC_K,    KC_H,    KC_COMM,       KC_DOT,         KC_QUES,
                  KC_LEFT,   KC_RIGHT,          KC_TAB,         HOME_SPACE,                            KC_BSPC,  LT_SYM_OSM_MEH,      KC_DOWN,           KC_UP
    ),
    [_SYMBOLS] = LAYOUT(
        PRINT_VID,   KC_F7,    KC_F8,   KC_F9,  KC_F10,                              _______, _______,    _______,  _______,    _______,
        PRINT,       KC_F4,    KC_F5,   KC_F6,  KC_F11,                              _______, _______,    _______,  _______,    _______,
        PRINT_CP,    KC_F1,    KC_F2,   KC_F3,  KC_F12,                              _______, _______,    _______,  _______,    _______,
                   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS,    QK_BOOT, DF(_GAME)
    ),
    [_MOUSE]      = LAYOUT(
        _______,     _______,    _______,    _______,    _______,                    KC_WH_L,    KC_WH_D,    KC_MS_U,  KC_WH_U,   KC_WH_R,
        _______,     _______,    _______,    _______,    _______,                    _______,    KC_MS_L,    KC_MS_D,  KC_MS_R,    KC_F12,
        _______,     KC_ACL2,    KC_ACL0,    KC_TRNS,    KC_BTN3,                    _______,    _______,    RTT_MSE,  _______,   _______,
                     KC_BTN4,    KC_BTN5,    KC_BTN2,    KC_BTN1,                    KC_BTN1,    KC_BTN2,    KC_WH_D,  KC_WH_U
    ),
    [_MOUSE_AUTO]      = LAYOUT( // have to duplicate to avoid the manual activation of layer from timing outt
        _______,     _______,    _______,    _______,    _______,                    _______, _______,    _______,  _______,    _______,
        _______,     _______,    _______,    _______,    _______,                    _______, _______,    _______,  _______,    _______,
        _______,     _______,    _______,    _______,    KC_BTN3,                    _______, _______,    RTT_MSE,  _______,    _______,
                    KC_BTN4,     KC_BTN5,    KC_BTN2,    KC_BTN1,                    KC_BTN1, KC_BTN2,    KC_WH_D,  KC_WH_U
    ),
    [_MOUSE_AUTO2]      = LAYOUT( // have to duplicate to avoid the manual activation of layer from timing outt
        _______,     _______,    _______,    _______,    _______,                    _______, _______,    _______,  _______,    _______,
        _______,     _______,    _______,    _______,    DRAG_SCROLL,                _______, _______,    _______,  _______,    _______,
        _______,     _______,    _______,    _______,    KC_BTN3,                    _______, _______,    RTT_MSE,  _______,    _______,
                    KC_BTN4,     KC_BTN5,    KC_BTN2,    KC_BTN1,                    KC_BTN1, KC_BTN2,    KC_WH_D,  KC_WH_U
    ),
    [_ARROW]      = LAYOUT(
       KC_NO,        KC_NO,    KC_UP,      KC_NO,   KC_NO,                               KC_PEQL,         KC_7,          KC_8,         KC_9,  KC_DLR,
     KC_HOME,      KC_LEFT,  KC_DOWN,    KC_RGHT,  KC_END,                               KC_PPLS,  RSFT_T(KC_4),  RGUI_T(KC_5), LALT_T(KC_6), KC_PERC,
        KC_Z,   KC_MS_BTN4,     KC_C, KC_MS_BTN5,    KC_V,                               KC_ASTR,         KC_1,          KC_2,         KC_3,  KC_PEQL,
                    KC_BTN4, KC_BTN5,     KC_TAB,  KC_SPC,                               WR_BSPC, KC_P0, KC_BSLS, KC_PDOT
    ),
    [_GAME] = LAYOUT(
        KC_TAB,        KC_Q,       KC_W,            KC_E,               KC_R,                               KC_Y,    KC_U,       KC_I,       KC_O,       KC_P,
       KC_LSFT,        KC_A,       KC_S,            KC_D,               KC_F,                               KC_H,    KC_J,       KC_K,       KC_L,    KC_SCLN,
       KC_LCTL,        KC_Z,       KC_X,            KC_C,               KC_V,                               KC_N,    KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,
                    KC_LALT,    KC_LGUI,        KC_SPACE,         MO(_GAME2),                            KC_BSPC,  KC_ENT,    KC_DOWN,      KC_UP
    ),
    [_GAME2] = LAYOUT(
        KC_TAB,       KC_F1,      KC_F2,           KC_F3,              KC_F4,                              KC_F5,   KC_F6,      KC_F7,      KC_F8,   KC_F9,
       KC_LSFT,        KC_1,       KC_2,            KC_3,               KC_4,                               KC_5,    KC_6,       KC_7,       KC_8,    KC_9,
       KC_LCTL,     KC_TILD,       KC_T,            KC_G,               KC_B,                            _______, _______,    _______,    _______,    _______,
                    KC_LEFT,   KC_RIGHT,         _______,            _______,                            _______, _______,    _______,    DF(_BASE)
    ),
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

// in keymap.c:
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE_AUTO2); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 64.0
#define SCROLL_DIVISOR_V 64.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate the angle of the vector
        int abs_x = abs(mouse_report.x);
        int abs_y = abs(mouse_report.y);

        // Determine if the movement is primarily horizontal or vertical
        if (abs_x > abs_y) {
            // Horizontal movements
            if (mouse_report.x > 5) {
                tap_code16(KC_RIGHT);
            } else if (mouse_report.x < -5) {
                tap_code16(KC_LEFT);
            }
        } else {
            // Vertical movements
            if (mouse_report.y > 5) {
                tap_code16(KC_DOWN);
            } else if (mouse_report.y < -5) {
                tap_code16(KC_UP);
            }
        }

        // Reset the horizontal and vertical scroll values
        mouse_report.h = 0;
        mouse_report.v = 0;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        // If scrolling is not active, proceed normally.
        mouse_report.x *= 1;
        mouse_report.y *= 1;
    }
    return mouse_report;
}

