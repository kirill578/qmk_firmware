#pragma once
#define SPLIT_USB_DETECT

// has to be disabled because of link time optimization
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define SELECT_SOFT_SERIAL_SPEED 1

#define OS_DETECTION_DEBOUNCE 200
#define OS_DETECTION_KEYBOARD_RESET

#define EE_HANDS
//#define SPLIT_HAND_PIN F4
//#define	SPLIT_HAND_PIN_LOW_IS_LEFT // seems flaky going with eproom for now

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_SHOULD_TRIGGER

#define PS2_MOUSE_USE_REMOTE_MODE

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 600
#define LEADER_NO_TIMEOUT

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0
#define MK_MOMENTARY_ACCEL

#define MOUSEKEY_INITIAL_SPEED	200
#define MOUSEKEY_BASE_SPEED		200
#define MK_3_SPEED 300

#define MK_C_OFFSET_UNMOD	16
#define MK_C_INTERVAL_UNMOD	2
#define MK_C_OFFSET_0	2
#define MK_C_INTERVAL_0	2


#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

#define BOOTMAGIC_ROW_RIGHT 4
#define BOOTMAGIC_COLUMN_RIGHT 4

#define NO_MUSIC_MODE

#define AUDIO_PIN C6

// #define NO_MUSIC_MODE
//#undef LOCKING_SUPPORT_ENABLE
//#undef LOCKING_RESYNC_ENABLE

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect

#define PS2_MOUSE_X_MULTIPLIER 1
#define PS2_MOUSE_Y_MULTIPLIER 1
#define PS2_MOUSE_V_MULTIPLIER 10

#define PS2_MOUSE_SCROLL_DIVISOR_H 32
#define PS2_MOUSE_SCROLL_DIVISOR_V -4
#define PS2_MOUSE_SCROLL_BTN_SEND 25 /* Default */

// #define PS2_MOUSE_SCROLL_DIVISOR_V -25
// #define PS2_MOUSE_SCROLL_DIVISOR_H 64


#define LAYER_STATE_8BIT
#define CIRQUE_PINNACLE_DIAMETER_MM 35
// #define CIRQUE_PINNACLE_TAP_ENABLE
// #define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define POINTING_DEVICE_ROTATION_90
//#define POINTING_DEVICE_AUTO_MOUSE_ENABLE

#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME	600
#define AUTO_MOUSE_DELAY 200 //	(Optional) Lockout time after non-mouse key is pressed	ideally (100-1000)	ms	TAPPING_TERM or 200 ms
#define AUTO_MOUSE_DEBOUNCE	25 // (Optional) Time delay from last activation to next update	ideally (10 - 100)	ms	25 ms
#define AUTO_MOUSE_THRESHOLD 20 //	(Optional) Amount of mouse movement required to switch layers	0 -	units	10 units

// #define PS2_MOUSE_ENABLE_SCROLLING
#define PS2_MOUSE_SCROLL_MASK 0x0
