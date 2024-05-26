#include QMK_KEYBOARD_H

#define PRINT LT(0,MEH(KC_F5))
enum layer_names {
    _BASE,
    _BASE2,
    _SYMBOLS,
    _MOUSE,
    _ARROW
};

float cutSound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_A3), Q__NOTE(_B3),);
float copySound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_B3),);
float pasteSound[][2] = SONG(Q__NOTE(_B3), Q__NOTE(_A3),);
float undoSound[][2] = SONG(Q__NOTE(_A3), Q__NOTE(_A3),);


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
        case LT(_ARROW,KC_SPC):
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
                    register_code(KC_BSPC);
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
                    unregister_code(KC_BSPC);
                    delkey_registered = false;
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
        case LT(0,KC_R):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_R)); // Intercept hold function to send Ctrl-R
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
        case LT(0,KC_LBRC):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_LBRC));
                return false;
            }
            return true;
        case LT(0,KC_RBRC):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_RBRC));
                return false;
            }
            return true;
        case LT(0,KC_SLSH):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_SLSH));
                return false;
            }
            return true;
        case LT(0,KC_QUOT):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_GRV);
                return false;
            }
            return true;
        case LT(0,KC_SCLN):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_SCLN));
                return false;
            }
            return true;
        case LT(0,KC_COMM):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_COMM));
                return false;
            }
            return true;
        case LT(0,KC_DOT):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_DOT));
                return false;
            }
            return true;
        case LT(0,KC_BSLS):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_BSLS));
                return false;
            }
            return true;
        case LT(0,KC_MINS):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_MINS));
                return false;
            }
            return true;
        case LT(0,KC_EQL):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(S(KC_EQL));
                return false;
            }
            return true;
        case PRINT:
            if (record->tap.count && record->event.pressed) {
                tap_code16(G(S(C((KC_F5)))));
            } else if (record->event.pressed) {
                tap_code16(G(S(KC_4)));
            }
            return false;
        case DEPLOYTEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("yarn build:test && yarn deploy:test\n");
            }
            return false;
        case INVALIATE:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("yarn invalidate-cache:test\n");
            }
            return false;
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
            if (!host_keyboard_led_state().num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            return true;
    }
    return true;
}

enum combos {
    TN_CW_TOGGLE,
    ST_OP,
    NE_CP,
    NI_DEL,
    _46_DEL,
    FP_OC,
    LU_CC,
    COMMA_DOT_MINUS
};

const uint16_t PROGMEM tn_cw_toggle[] = {HOME_T, HOME_N, COMBO_END};
const uint16_t PROGMEM st_op[] = {HOME_S, HOME_T, COMBO_END};
const uint16_t PROGMEM ne_cp[] = {HOME_N, HOME_E, COMBO_END};
const uint16_t PROGMEM ni_del[] = {HOME_N, HOME_I, COMBO_END};
const uint16_t PROGMEM _46_del[] = {RSFT_T(KC_P4), LALT_T(KC_P6), COMBO_END};
const uint16_t PROGMEM fp_oc[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lu_cc[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM comma_dot_minus[] = {KC_COMM, KC_DOT, COMBO_END};


combo_t key_combos[] = {
    [TN_CW_TOGGLE] = COMBO(tn_cw_toggle, CW_TOGG),
    [ST_OP] = COMBO(st_op, S(KC_9)),
    [NE_CP] = COMBO(ne_cp, S(KC_0)),
    [NI_DEL] = COMBO(ni_del, KC_DEL),
    [_46_DEL] = COMBO(_46_del, KC_DEL),
    [FP_OC] = COMBO(fp_oc, KC_LCBR),
    [LU_CC] = COMBO(lu_cc, KC_RCBR),
    [COMMA_DOT_MINUS] = COMBO(comma_dot_minus, KC_MINS)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,        KC_W,       KC_F,            KC_P,               KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,  LT(0,KC_QUOT),
      HOME_A,      HOME_R,     HOME_S,          HOME_T,             HOME_G,                             HOME_M,  HOME_N,  HOME_E,  HOME_I,         HOME_O,
  LT(0,KC_Z),  LT(0,KC_X), LT(0,KC_C), LT(_MOUSE,KC_D),         LT(0,KC_V),                               KC_K,    KC_H,    KC_COMM, KC_DOT,      KC_SLSH,
                  KC_LEFT,   KC_RIGHT,          KC_TAB,  LT(_ARROW,KC_SPC),                               KC_BSPC, LT(_SYMBOLS,KC_ENT), KC_LPRN,  KC_RPRN
    ),
    [_BASE2]      = LAYOUT(
        KC_Q,         KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,         KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,         KC_X,    KC_C,    KC_D,    KC_V,                               KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                  KC_LEFT, KC_RIGHT,  KC_TAB,  KC_SPC,                               KC_BSPC, KC_ENT, KC_LPRN, KC_RPRN
    ),
    [_SYMBOLS] = LAYOUT(
        KC_Q,         KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,         KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,         KC_X,    KC_C,    KC_D,    KC_V,                               KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                  KC_LEFT, KC_RIGHT,  KC_TAB,  KC_SPC,                               KC_BSPC, KC_ENT, KC_LPRN, KC_RPRN
    ),
    [_MOUSE]      = LAYOUT(
        KC_Q,         KC_W,    KC_F,    KC_P,    KC_B,                               KC_J, KC_WH_D,    KC_MS_U, KC_WH_U,    KC_QUOT,
        KC_A,         KC_R,    KC_S,    KC_T,    KC_G,                               KC_M, KC_MS_L,    KC_MS_D, KC_MS_R,    KC_O,
        KC_Z,      KC_ACL2, KC_ACL0, KC_TRNS,    KC_V,                               KC_K,    KC_H,    RTT_MSE, KC_DOT,  KC_SLSH,
                  KC_LEFT, KC_RIGHT,  KC_TAB, KC_BTN3,                               KC_BTN1, KC_BTN2, KC_LPRN, KC_RPRN
    ),
    [_ARROW]      = LAYOUT(
       KC_NO,        KC_NO,    KC_UP,      KC_NO,   KC_NO,                               KC_NO,  KC_P7,          KC_P8,                     KC_P9,                     KC_PPLS,
     KC_HOME,      KC_LEFT,  KC_DOWN,    KC_RGHT,  KC_END,                               KC_NO,  RSFT_T(KC_P4),  RGUI_T(KC_P5),             LALT_T(KC_P6),             RCTL_T(KC_PCMM),
        KC_Z,   KC_MS_BTN4,     KC_C, KC_MS_BTN5,    KC_V,                               KC_P0,  KC_P1,   KC_P2,  KC_P3, KC_PEQL,
                   KC_LEFT, KC_RIGHT,     KC_TAB,  KC_SPC,                               KC_BSPC, KC_PENT, KC_LPRN, KC_PDOT
    )
};
