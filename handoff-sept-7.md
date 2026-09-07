## Handoff summary

 User is configuring a **Silakka54 split keyboard**, using only the **42 non-top-row keys**, for full-time software development and occasional gaming. They are transitioning from traditional QWERTY/hunt-and-peck typing to touch typing and want to preserve familiar QWERTY muscle memory while improving ergonomics.

 User prefers **concise answers**, not lengthy explanations.

 ### Current Alpha layer — committed

```
// ALPHA
[0] = LAYOUT(
    KC_0,       KC_1,    KC_2,    KC_3,     KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_MINS,  KC_EQL,
    QK_GESC,    KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     TD(TD_LBRC),
    QK_LEAD,    KC_A,    KC_S,    KC_D,     KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                                  KC_LCTL,  KC_LGUI, LT(2,KC_SPC),    LT(1,KC_SPC),     KC_BSPC, KC_ENT
),
```

 Thumb logic:

```
LCTL   LGUI   NAV+Space     BETA+Space   BSPC   ENT
              LT(2,SPC)     LT(1,SPC)
```

 Left thumb Space remains available to preserve user's existing muscle memory; holding it accesses **NAV layer 2**. Right thumb Space accesses **BETA layer 1**.

 ### Planned Alpha behavior

 - `Esc` tap → Escape; hold → momentary **SYS layer**.
  - Likely `LT(3, KC_ESC)` if SYS is layer 3.
- `KC_LBRC`:
  - single tap → `[`
  - double tap → `]`
- `KC_QUOT`:
  - single tap → `'`
  - double tap → `Shift + KC_QUOT` → `"`
- Decided **not** to auto-pair `''`, `""`, `[]`, `{}`, `()` via QMK; editor auto-pairing is preferable for syntactic pairs.
- `QK_LEAD` should ideally:
  - tap → Leader
  - hold → layer lock, eventually to be implemented.
- Alpha should remain predictable and close to standard QWERTY.

 ### Tap Dance conclusions

 User provided the full QMK Tap Dance documentation. Key points understood:

 - `TAP_DANCE_ENABLE = yes` enables the subsystem.
- `TD(x)` is the actual Tap Dance keycode placed in `LAYOUT()`.
- `x`/`TD_FOO` is merely the index into `tap_dance_actions[]`.
- Basic actions:
  - `ACTION_TAP_DANCE_DOUBLE(kc1, kc2)`
  - layer move/toggle variants
- Advanced actions:
  - `ACTION_TAP_DANCE_FN(fn)`
  - `ACTION_TAP_DANCE_FN_ADVANCED(...)`
  - can execute arbitrary QMK C logic, `tap_code16`, `register_code16`, `SEND_STRING`, layers, etc.
- Therefore Tap Dance **can** perform programmable/macro-like behavior; it isn't limited to basic keycodes.
- `TAPPING_TERM` controls the maximum interval between taps.
- Current setting:

```
#define TAPPING_TERM 200
```

 - `TAPPING_TERM_PER_KEY` is **not currently needed**.
- Tap Dance can handle interruptions and tap counts; `state->count`, `state->pressed`, `state->interrupted`, and `state->finished` are relevant in advanced dances.
- QMK's docs recommend Tap Dance primarily on non-letter / less frequently doubled keys. `[` and `'` are reasonable candidates.
- Trailing commas in C initializers are optional; conventional but not required.

 ### Current `config.h` relevant section

```
#define ENABLE_COMPILE_KEYCODE

#define TAPPING_TERM 200
// #define TAPPING_TERM_PER_KEY
```

 ### Current `rules.mk`

```
CAPS_WORD_ENABLE = yes
LAYER_LOCK_ENABLE = yes

TAP_DANCE_ENABLE = yes

LEADER_ENABLE = yes
KEY_LOCK_ENABLE = yes
```

 ### Current Tap Dance code / issue discovered

 User initially had:

```
enum {
    TD_SAFETY_DANCE,
    TD_LBRC
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
};
```

 Mistakes identified:

 1. Missing comma was pointed out, though trailing comma is optional.
2. More importantly, they used:

```
TD_LBRC
```

 inside `LAYOUT()`, which is only the enum/index.

 Correct:

```
TD(TD_LBRC)
```

 Important mental model:

```
TD_LBRC      = index used by tap_dance_actions[]
TD(TD_LBRC)  = actual keycode placed in the keymap
```

 ### Safety Dance test

 User wants to implement the QMK documentation's "Safety Dance" example as a test.

 Correct minimal implementation:

```
enum {
    TD_SAFETY_DANCE,
    TD_LBRC,
};

void dance_safety(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 5) {
        SEND_STRING("Safety dance!");
        reset_tap_dance(state);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SAFETY_DANCE] = ACTION_TAP_DANCE_FN(dance_safety),
    [TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
};
```

 To test, temporarily place:

```
TD(TD_SAFETY_DANCE)
```

 on a physical key. Five taps should emit:

```
Safety dance!
```

 The Safety Dance function **must be registered** in `tap_dance_actions[]`; merely defining the function does nothing.

 ### Immediate next task

 Finish **Alpha** before moving to Beta.

 First implement/test Tap Dance infrastructure, then implement:

```
TD_LBRC:
tap       → [
double    → ]

TD_QUOT:
tap       → '
double    → Shift+' → "
```

 For `TD_LBRC`, basic:

```
[TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
```

 is sufficient.

 For `TD_QUOT`, use an advanced Tap Dance callback because the double-tap action is effectively `Shift + KC_QUOT`, rather than another basic keycode.

 Then address:

```
QK_GESC hold → SYS layer
QK_LEAD tap → Leader
QK_LEAD hold → layer lock
```

 Only after Alpha is finished should we move to **BETA layer 1**.

 ### Communication preference

 Be **concise and technical**. User explicitly objected to overly long answers. Give the relevant code and a short explanation. Avoid re-explaining QMK fundamentals unless needed.
