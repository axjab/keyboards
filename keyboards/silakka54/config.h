
// status: WIP
// date: 2026-09-06

#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17


// ADDED BY ME: ///////////////////////////////////////

// ref
#define ENABLE_COMPILE_KEYCODE

// TAP DANCE SECTION ////////////////////////////////////
// Ref: https://docs.qmk.fm/features/tap_dance
#define TAPPING_TERM 200
// #define TAPPING_TERM_PER_KEY

// notes:
// The TAPPING_TERM_PER_KEY definition is only needed if you control the tapping term through a custom get_tapping_term function, which may be needed because TAPPING_TERM affects not just tap-dance keys.

// TAP DANCE END

// QMK Keycodes
// Key	Aliases	Description
// QK_BOOTLOADER	QK_BOOT	Put the keyboard into bootloader mode for flashing
// QK_DEBUG_TOGGLE	DB_TOGG	Toggle debug mode
// QK_CLEAR_EEPROM	EE_CLR	Reinitializes the keyboard's EEPROM (persistent memory)
// QK_MAKE		Sends qmk compile -kb (keyboard) -km (keymap), or qmk flash if shift is held. Puts keyboard into bootloader mode if shift & control are held
// QK_REBOOT	QK_RBT	Resets the keyboard. Does not load the bootloader
// WARNING
