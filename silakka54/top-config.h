
// ref
#define ENABLE_COMPILE_KEYCODE

// https://docs.qmk.fm/features/tap_dance
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY


// QMK Keycodes
// Key	Aliases	Description
// QK_BOOTLOADER	QK_BOOT	Put the keyboard into bootloader mode for flashing
// QK_DEBUG_TOGGLE	DB_TOGG	Toggle debug mode
// QK_CLEAR_EEPROM	EE_CLR	Reinitializes the keyboard's EEPROM (persistent memory)
// QK_MAKE		Sends qmk compile -kb (keyboard) -km (keymap), or qmk flash if shift is held. Puts keyboard into bootloader mode if shift & control are held
// QK_REBOOT	QK_RBT	Resets the keyboard. Does not load the bootloader
// WARNING
