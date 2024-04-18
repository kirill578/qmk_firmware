
#include QMK_KEYBOARD_H

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define PRINT LT(0,MEH(KC_F5))

enum layer_names {
    _BASE,
    _SYMBOLS,
    _MOUSE,
    _ARROW
};

enum custom_keycodes {
    DEPLOYTEST = SAFE_RANGE,
    INVALIATE,
};

// search str

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
    switch (keycode) {
        case LT(0,KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(useCMD ? G(KC_X) : C(KC_X));
                return false;
            }
            return true;
        case LT(0,KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(useCMD ? G(KC_C) : C(KC_C));
                return false;
            }
            return true;
        case LT(0,KC_V):
            if (!record->tap.count && record->event.pressed) {
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
                tap_code16(S(KC_QUOT));
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
                tap_code16(MEH(KC_F5));
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
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
QK_GESC,    KC_1,           KC_2,           KC_3,               KC_4,           KC_5,     /**/       KC_6,   KC_7,           KC_8,                      KC_9,                       KC_0,            LT(0, KC_EQL),
KC_TAB,     KC_Q,           KC_W,           KC_E,               LT(0,KC_R),     KC_T,     /**/       KC_Y,   KC_U,           KC_I,                      KC_O,                       KC_P,            LT(0, KC_MINS),
CW_TOGG,    LCTL_T(KC_A),   LSFT_T(KC_S),   LGUI_T(KC_D),       LALT_T(KC_F),   KC_G,     /**/       KC_H,   LALT_T(KC_J),   LGUI_T(KC_K),              LSFT_T(KC_L),               LCTL_T(KC_SCLN), LT(0, KC_QUOT),
PRINT,      LT(0,KC_Z),     LT(0,KC_X),     LT(0,KC_C),         LT(0,KC_V),     KC_B,     /**/       KC_N,   KC_M,           LT(0, KC_COMM),            LT(0, KC_DOT),              LT(0, KC_SLSH),  LT(0, KC_BSLS),
KC_NO,      KC_NO,          KC_LPRN,        KC_RPRN,                                      /**/                               LT(0, KC_LBRC),            LT(0, KC_RBRC),             KC_NO,           KC_NO,

                                               TT(_MOUSE),  LT(_ARROW,KC_SPC),   KC_BSPC, /**/     KC_DEL,    KC_ENT,     MO(_SYMBOLS)
    ),

    [_SYMBOLS] = LAYOUT(
KC_TRNS,    KC_F1,          KC_F2,          KC_F3,              KC_F4,          KC_F5,    /**/       KC_F6,   KC_F7,          KC_F8,                    KC_F9,                     KC_F10,          KC_DEL,
KC_NO,      KC_1,           KC_2,           KC_3,               KC_4,           KC_5,     /**/       KC_6,    KC_7,           KC_8,                     KC_9,                       KC_0,            KC_PLUS,
KC_TRNS,    KC_EXLM,        KC_AT,          KC_HASH,            KC_DLR,         KC_PERC,  /**/       KC_CIRC, KC_AMPR,        KC_ASTR,                  S(KC_BSLS),                 KC_PLUS,         KC_PIPE,
KC_TRNS,    KC_GRV,         KC_QUOT,        S(KC_QUOT),         S(KC_SLSH),     KC_GRV,   /**/       KC_TRNS, KC_PLUS,        KC_MINS,                  KC_EQL,                     KC_UNDS,         KC_NO,
KC_NO,      KC_NO,          KC_LCBR,        KC_RCBR,                                      /**/                                KC_LPRN,                  KC_RPRN,                    KC_NO,           KC_NO,

                                                    KC_TRNS,    KC_TRNS,        KC_TRNS,  /**/  KC_TRNS,  KC_TRNS,   KC_TRNS
    ),

    [_MOUSE] = LAYOUT(
KC_F12,     KC_F1,          KC_F2,          KC_F3,              KC_F4,          KC_F5,    /**/       KC_F6,   KC_F7,          KC_F8,                     KC_F9,                     KC_F10,          KC_F11,
KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_WH_U,            KC_TRNS,        KC_TRNS,  /**/       KC_TRNS, KC_TRNS,        KC_MS_U,                   KC_TRNS,                   KC_TRNS,         KC_TRNS,
KC_TRNS,    KC_ACL1,        KC_WH_L,        KC_WH_D,            KC_WH_R,        KC_TRNS,  /**/       KC_TRNS, KC_MS_L,        KC_MS_D,                   KC_MS_R,                   KC_ACL2,         KC_TRNS,
KC_TRNS,    KC_BTN3,        MEH(KC_F1),     MEH(KC_F2),         MEH(KC_F3),     KC_TRNS,  /**/       KC_TRNS, KC_TRNS,        KC_TRNS,                   KC_NO,                     KC_NO,           KC_NO,
KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,                                      /**/                                KC_TRNS,                   KC_TRNS,                   KC_NO,           KC_NO,

                                                    KC_TRNS,    KC_TRNS,        KC_TRNS,  /**/  KC_BTN2,  KC_BTN1,    KC_BTN3
    ),

    [_ARROW] = LAYOUT(
QK_BOOT,    DEPLOYTEST,     INVALIATE,      KC_NO,              KC_NO,          KC_NO,    /**/       KC_NO,  KC_NO,          KC_PSLS,                   KC_PAST,                   KC_PMNS,         KC_NO,
KC_NO,      KC_NO,          KC_NO,          KC_UP,              KC_NO,          KC_NO,    /**/       KC_NO,  KC_P7,          KC_P8,                     KC_P9,                     KC_PPLS,         KC_NO,
KC_NO,      KC_HOME,        KC_LEFT,        KC_DOWN,            KC_RGHT,        KC_END,   /**/       KC_NO,  LGUI_T(KC_P4),  LGUI_T(KC_P5),             LSFT_T(KC_P6),             LCTL_T(KC_PCMM), KC_NO,
KC_NO,      KC_NO,          KC_MS_BTN4,     KC_NO,              KC_MS_BTN5,     KC_NO,    /**/       KC_NO,  KC_P0,          KC_P1,                     KC_P2,                     KC_P3,           KC_PEQL,
KC_NO,      KC_NO,          KC_NO,          KC_NO,                                        /**/                               KC_PENT,                   KC_PDOT,                   KC_NO,           KC_NO,

                                                    KC_TRNS,    KC_LCTL,        KC_BSPC,  /**/  KC_DEL,    KC_NO,      KC_NO
    )
};
