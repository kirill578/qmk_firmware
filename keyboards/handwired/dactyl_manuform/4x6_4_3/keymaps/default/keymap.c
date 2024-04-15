
#include QMK_KEYBOARD_H

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
    _ARROW
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
QK_GESC,    KC_1,           KC_2,           KC_3,               KC_4,           KC_5,     /**/       KC_6,   KC_7,           KC_8,                      KC_9,                       KC_0,            KC_BSPC,
KC_TAB,     KC_Q,           KC_W,           KC_E,               KC_R,           KC_T,     /**/       KC_Y,   KC_U,           KC_I,                      KC_O,                       KC_P,            KC_MINS,
KC_CAPS,    LCTL_T(KC_A),   LSFT_T(KC_S),   LGUI_T(KC_D),       LALT_T(KC_F),   KC_G,     /**/       KC_H,   LALT_T(KC_J),   LGUI_T(KC_K),              LSFT_T(KC_L),               LCTL_T(KC_SCLN), KC_QUOT,
KC_LSFT,    KC_Z,           KC_X,           KC_C,               KC_V,           KC_B,     /**/       KC_N,   KC_M,           KC_COMM,                   KC_DOT,                     KC_SLSH,         KC_BSLS,
KC_NO,      KC_NO,          KC_LPRN,        KC_RPRN,                                      /**/                               MT(LSFT(KC_9), KC_LBRC),   MT(LSFT(KC_0), KC_RBRC),    KC_NO,           KC_NO,

                                                     TT(2),      LT(3,KC_SPC),   KC_BSPC, /**/  KC_DEL,    KC_ENT,     MO(1)
    ),

    [_LOWER] = LAYOUT(
KC_TRNS,    KC_F1,          KC_F2,          KC_F3,              KC_F4,          KC_F5,    /**/       KC_F6,   KC_F7,          KC_F8,                    KC_F9,                     KC_F10,          KC_DEL,
KC_NO,      KC_1,           KC_2,           KC_3,               KC_4,           KC_5,     /**/       KC_6,    KC_7,           KC_8,                     KC_9,                       KC_0,            KC_PLUS,
KC_TRNS,    KC_EXLM,        KC_AT,          KC_HASH,            KC_DLR,         KC_PERC,  /**/       KC_CIRC, KC_AMPR,        KC_ASTR,                  KC_LPRN,                    KC_RPRN,         KC_PIPE,
KC_TRNS,    KC_TRNS,        KC_LCBR,        KC_RCBR,            KC_TRNS,        KC_TRNS,  /**/       KC_TRNS, KC_LT,          KC_GT,                    KC_EQL,                     KC_UNDS,         KC_NO,
KC_NO,      KC_NO,          KC_TRNS,        KC_TRNS,                                      /**/                                KC_LPRN,                  KC_RPRN,                    KC_NO,           KC_NO,

                                                    KC_TRNS,    KC_TRNS,        KC_TRNS,  /**/  KC_TRNS,  KC_TRNS,   KC_TRNS
    ),

    [_RAISE] = LAYOUT(
KC_F12,     KC_F1,          KC_F2,          KC_F3,              KC_F4,          KC_F5,    /**/       KC_F6,   KC_F7,          KC_F8,                     KC_F9,                     KC_F10,          KC_F11,
KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_WH_U,            KC_TRNS,        KC_TRNS,  /**/       KC_TRNS, KC_TRNS,        KC_MS_U,                   KC_TRNS,                   KC_TRNS,         KC_TRNS,
KC_TRNS,    KC_ACL0,        KC_ACL1,        KC_WH_L,            KC_WH_D,        KC_WH_R,  /**/       KC_TRNS, KC_TRNS,        KC_MS_L,                   KC_MS_D,                   KC_MS_R,         KC_ACL2,
KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_BTN3,        KC_TRNS,  /**/       KC_TRNS, KC_TRNS,        KC_TRNS,                   KC_NO,                     KC_NO,           KC_NO,
KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,                                      /**/                                KC_TRNS,                   KC_TRNS,                   KC_NO,           KC_NO,

                                                    KC_TRNS,    KC_TRNS,        KC_TRNS,  /**/  KC_BTN2,  KC_BTN1,    KC_BTN3
    ),

    [_ARROW] = LAYOUT(
KC_NO,      KC_NO,          KC_NO,          KC_NO,              KC_NO,          KC_NO,    /**/       KC_NO,  KC_NO,          KC_PSLS,                   KC_PAST,                   KC_PMNS,         KC_NO,
KC_NO,      KC_NO,          KC_NO,          KC_UP,              KC_NO,          KC_NO,    /**/       KC_NO,  KC_P7,          KC_P8,                     KC_P9,                     KC_PPLS,         KC_NO,
KC_NO,      KC_HOME,        KC_LEFT,        KC_DOWN,            KC_RGHT,        KC_END,   /**/       KC_NO,  LGUI_T(KC_P4),  LGUI_T(KC_P5),             LSFT_T(KC_P6),             LCTL_T(KC_PCMM), KC_NO,
KC_NO,      KC_NO,          KC_NO,          KC_NO,              KC_NO,          KC_NO,    /**/       KC_NO,  KC_P0,          KC_P1,                     KC_P2,                     KC_P3,           KC_PEQL,
KC_NO,      KC_NO,          KC_NO,          KC_NO,                                        /**/                               KC_PENT,                   KC_PDOT,                   KC_NO,           KC_NO,

                                                    KC_TRNS,    KC_LCTL,        KC_BSPC,  /**/  KC_DEL,    KC_NO,      KC_NO
    )
};
