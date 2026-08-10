#define MIRYOKU_CLIPBOARD_MAC

// Hyper = Cmd+Ctrl+Alt+Shift (used by Raycast hotkeys to avoid collisions)
#define HYPER(K) &kp LC(LS(LA(LG(K))))

// Layer list. The stock layout has 10 layers. EXTRA, TAP, and BUTTON are removed
// here because nothing on this keyboard can reach them: BASE has no BUTTON
// layer-tap, and the jump keys that led to EXTRA and TAP are also removed.
// MOUSE holds the Raycast layer and MEDIA holds the Mac layer. The slot names
// stay the same so that the generated files continue to build.
#define MIRYOKU_LAYER_LIST \
MIRYOKU_X(BASE,  "Base") \
MIRYOKU_X(NAV,   "Nav") \
MIRYOKU_X(MOUSE, "Raycast") \
MIRYOKU_X(MEDIA, "Mac") \
MIRYOKU_X(NUM,   "Num") \
MIRYOKU_X(SYM,   "Sym") \
MIRYOKU_X(FUN,   "Fun")

#define U_BASE   0
#define U_NAV    1
#define U_MOUSE  2
#define U_MEDIA  3
#define U_NUM    4
#define U_SYM    5
#define U_FUN    6

// No layer can lock. Stock Miryoku puts a layer lock key and a layer jump key on
// the bottom row of every hold layer. Both use &to, so the layer stays on after
// you release the thumb key. They sit under the alphas you type most, and a
// double tap there locked a layer by accident. All of them are U_NU here.
// &u_to_U_BASE stays as the escape key, and it is the only &to key left.

// Home-row mods use a separate behavior for each hand. Both are defined in
// config/corne.keymap, because the key position lists are specific to the Corne.
#define U_HML(MOD, TAP) &u_hml MOD TAP
#define U_HMR(MOD, TAP) &u_hmr MOD TAP

// Base: Colemak-DH with home-row mods. The outer pinkies (Z and /) are plain
// keys, not layer-taps.
#define MIRYOKU_LAYER_BASE \
&kp Q,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,           \
U_HML(LCTRL, A),   U_HML(LALT, R),    U_HML(LGUI, S),    U_HML(LSHFT, T),   &kp G,             &kp M,             U_HMR(LSHFT, N),   U_HMR(LGUI, E),    U_HMR(LALT, I),    U_HMR(LCTRL, O),   \
&kp Z,             U_HML(RALT, X),    &kp C,             &kp D,             &kp V,             &kp K,             &kp H,             &kp COMMA,         U_HMR(RALT, DOT),  &kp SLASH,         \
U_NP,              U_NP,              U_LT(U_MEDIA, ESC),U_LT(U_NAV, SPACE),U_LT(U_MOUSE, TAB),U_LT(U_SYM, RET),  U_LT(U_NUM, BSPC), U_LT(U_FUN, DEL),  U_NP,              U_NP

// Nav (held by Space). Trimmed to the keys in daily use: an inverted-T arrow
// cluster and caps word. Up sits on the U slot, directly above Down on E. Left
// keeps the index finger and Down the middle finger. Right moves in one column,
// from the pinky to the ring finger, so that the three flat arrows are adjacent.
// The left-hand mod row stays. Base-layer home-row mods are not active on this
// layer, so this row is the only way to send Shift+Arrow, Opt+Arrow or
// Cmd+Arrow while Nav is on.
// The clipboard row, Ins, Home, End, PgUp, PgDn and the right thumbs are free.
// Boot is no longer on this layer, because a stray press while you hold Space
// dropped the board into the bootloader. It is still on Mac, Num, Sym and Fun.
#define MIRYOKU_LAYER_NAV \
U_NU,              U_NU,              U_NU,              U_NU,              U_NA,              U_NU,              U_NU,              &kp UP,            U_NU,              U_NU,              \
&kp LCTRL,         &kp LALT,          &kp LGUI,          &kp LSHFT,         U_NA,              &u_caps_word,      &kp LEFT,          &kp DOWN,          &kp RIGHT,         U_NU,              \
U_NA,              &kp RALT,          U_NU,              U_NU,              U_NA,              U_NU,              U_NU,              U_NU,              U_NU,              U_NU,              \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_NU,              U_NU,              U_NU,              U_NP,              U_NP

// Raycast layer (held by Tab, occupies the MOUSE slot).
// Each alpha sends Hyper+<letter>; bind these in Raycast (e.g. Hyper+S -> Slack).
// Letter positions mirror the Colemak-DH base layer so muscle memory carries over.
#define MIRYOKU_LAYER_MOUSE \
HYPER(Q),          HYPER(W),          HYPER(F),          HYPER(P),          HYPER(B),          HYPER(J),          HYPER(L),          HYPER(U),          HYPER(Y),          HYPER(SQT),        \
HYPER(A),          HYPER(R),          HYPER(S),          HYPER(T),          HYPER(G),          HYPER(M),          HYPER(N),          HYPER(E),          HYPER(I),          HYPER(O),          \
HYPER(Z),          HYPER(X),          HYPER(C),          HYPER(D),          HYPER(V),          HYPER(K),          HYPER(H),          HYPER(COMMA),      HYPER(DOT),        HYPER(SLASH),      \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// Mac layer (held by Esc, occupies the MEDIA slot).
// C = screenshot, capture selected portion (Cmd+Shift+4)
// N = previous Space / "swipe left between apps" (Ctrl+Left)
// I = next Space / "swipe right between apps" (Ctrl+Right)
// E = volume down, U = volume up (U sits directly above E)
// D = dictation. Sends F13; assign the same key in
// System Settings > Keyboard > Dictation > Shortcut > Customize.
// Bottom row, right hand: USB/BLE output toggle and Bluetooth profiles 0 to 3.
// Tap selects the profile. Shift plus tap also clears the pairing on it.
// These are the only keys that can reach the radio, so keep them bound.
#define MIRYOKU_LAYER_MEDIA \
U_BOOT,            U_NU,              U_NU,              &u_to_U_BASE,      U_NA,              U_NU,              U_NU,              &kp C_VOL_UP,      U_NU,              U_NU,              \
&kp LCTRL,         &kp LALT,          &kp LGUI,          &kp LSHFT,         U_NA,              U_NU,              &kp LC(LEFT),      &kp C_VOL_DN,      &kp LC(RIGHT),     U_NU,              \
U_NA,              &kp RALT,          &kp LS(LG(N4)),    &kp F13,           U_NU,              &u_out_tog,        &u_bt_sel_0,       &u_bt_sel_1,       &u_bt_sel_2,       &u_bt_sel_3,       \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp C_STOP,        &kp C_PP,          &kp C_MUTE,        U_NP,              U_NP

// Num (held by Backspace). Same as stock, minus the EXTRA and TAP jump keys.
#define MIRYOKU_LAYER_NUM \
&kp LBKT,          &kp N7,            &kp N8,            &kp N9,            &kp RBKT,          U_NA,              &u_to_U_BASE,      U_NU,              U_NU,              U_BOOT,            \
&kp SEMI,          &kp N4,            &kp N5,            &kp N6,            &kp EQUAL,         U_NA,              &kp LSHFT,         &kp LGUI,          &kp LALT,          &kp LCTRL,         \
&kp GRAVE,         &kp N1,            &kp N2,            &kp N3,            &kp BSLH,          U_NA,              U_NU,              U_NU,              &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp DOT,           &kp N0,            &kp MINUS,         U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// Sym (held by Return). Each symbol sits on the letter that names it: @ on A,
// $ on D, = on E, £ on G for GBP, # on H, - on M, % on P, * on S, ~ on T, and
// ! on X for eXclamation. Two go by shape instead: | on L, because the letter
// looks like a pipe, and ^ on U, because the caret points up.
//
// < = > sit side by side on N, E and I, in reading order, so <= and >= are an
// inward roll on the index, middle and ring fingers. The O pinky is free.
//
// { } & + and the three thumb keys keep their stock positions, because those
// symbols have no letter of their own.
//
// Two consequences. This layer no longer mirrors Num with Shift held. And the
// right hand now carries symbols in place of the mirror mods, so Cmd+- and
// Cmd+= must come from Num, which keeps its own mod set. ->Base moves to the
// Y position, beside Boot, because | takes the L position.
//
// £ assumes the macOS US English input source, where Option+3 emits the pound
// sign. On the British input source, change LA(N3) to LS(N3).
#define MIRYOKU_LAYER_SYM \
&kp LBRC,          &kp AMPS,          &kp PLUS,          &kp PRCNT,         &kp RBRC,          U_NA,              &kp PIPE,          &kp CARET,         &u_to_U_BASE,      U_BOOT,            \
&kp AT,            &kp COLON,         &kp ASTRK,         &kp TILDE,         &kp LA(N3),        &kp MINUS,         &kp LESS_THAN,     &kp EQUAL,         &kp GREATER_THAN,  U_NU,              \
U_NU,              &kp EXCL,          U_NU,              &kp DLLR,          U_NU,              U_NA,              &kp HASH,          U_NU,              &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp LPAR,          &kp RPAR,          &kp UNDER,         U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// Fun (held by Delete). Stock function-key layout, minus the EXTRA and TAP
// jump keys.
#define MIRYOKU_LAYER_FUN \
&kp F12,           &kp F7,            &kp F8,            &kp F9,            &kp PSCRN,         U_NA,              &u_to_U_BASE,      U_NU,              U_NU,              U_BOOT,            \
&kp F11,           &kp F4,            &kp F5,            &kp F6,            &kp SLCK,          U_NA,              &kp LSHFT,         &kp LGUI,          &kp LALT,          &kp LCTRL,         \
&kp F10,           &kp F1,            &kp F2,            &kp F3,            &kp PAUSE_BREAK,   U_NA,              U_NU,              U_NU,              &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp K_APP,         &kp SPACE,         &kp TAB,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP
