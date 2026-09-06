
// ERROR:
ACTION_TAP_DANCE_DOUBLE(SHIFT, LOCK):
  // Sends the kc1 keycode when tapped once, kc2 otherwise.
  // When the key is held, the appropriate keycode is registered:
  // kc1 when pressed and held, kc2 when tapped once, then pressed and held.
