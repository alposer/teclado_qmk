#include QMK_KEYBOARD_H
//Capas
#define _BAS 0
#define _FUN 1
#define _NUM 2

#define MOD_LCLALS MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT)

//Teclas
//KC_LSPO y KC_RSPC son teclas predefinidas de space_cadet
//KC_LCPO y KC_RCPC son teclas predefinidas de space_cadet


//-------FUNCIONES PARA TAPDANCE DE LA TECLA ALT

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
} td_state_t;

static td_state_t td_state;

int cur_dance (qk_tap_dance_state_t *state);
void gui_alt_finished (qk_tap_dance_state_t * state, void *user_data);
void gui_alt_reset (qk_tap_dance_state_t* state, void *user_data);

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count ==  1) {
    if (state->interrupted || !state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else {
    return 2;
  }
};

void gui_alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      set_oneshot_mods(MOD_LCLALS);//(L/R)SHIFT + (L/R)ALT + (L/R)GUI
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LALT));
      break;
  }
};

void gui_alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      clear_oneshot_mods();
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LALT));
      break;
  }
};



// Tap Dance
enum {
    TD_INS_EXEC,
    TD_F12,
    TD_LALT,
		TD_HOME,
		TD_END,
		TD_H }; 

// Tap Dance definiciones
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_INS_EXEC] = ACTION_TAP_DANCE_DOUBLE(KC_INSERT,KC_EXECUTE),
    [TD_F12] = ACTION_TAP_DANCE_DOUBLE(KC_F12,MEH(KC_F12)),
    [TD_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_alt_finished, gui_alt_reset),
    [TD_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_HOME,C(KC_HOME)),
    [TD_END] = ACTION_TAP_DANCE_DOUBLE(KC_END,C(KC_END)),
    [TD_H] = ACTION_TAP_DANCE_DOUBLE(KC_H,C(KC_H))
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BAS] = LAYOUT_75_iso(
	/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
		 KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,  TD(TD_F12),   KC_PSCR,  TD(TD_INS_EXEC),  KC_DEL,
	/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┤ */
		 KC_GRV,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,  KC_EQL,        KC_BSPC,       TD(TD_HOME),
	/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┤ */
		 KC_TAB, 	     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,    KC_LBRC,  KC_RBRC,                 TD(TD_END),
	/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬           ├─────────┤ */
		 KC_CAPS,           KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     TD(TD_H),     KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_QUOT,  KC_NUHS,   KC_ENT,    KC_PGUP,
	/* ├───────────┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴─────────┴─┬─────────┼─────────┤ */
		 KC_LSPO,   KC_NUBS,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,      KC_RSPC,       KC_UP,   KC_PGDN,
	/* ├───────────┼─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┼─────────┤ */
		 KC_LCPO,     KC_LGUI,  TD(TD_LALT),                          KC_SPC,                                  KC_RALT, MO(_FUN),  KC_RCPC,  KC_LEFT,  KC_DOWN,  KC_RGHT
	/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
    ),

	[_FUN] = LAYOUT_75_iso(
	/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
        KC_ESC,MEH(KC_F1),MEH(KC_F2),MEH(KC_F3),MEH(KC_F4),MEH(KC_F5),MEH(KC_F6),MEH(KC_F7),MEH(KC_F8),MEH(KC_F9),MEH(KC_F10),MEH(KC_F11),MEH(KC_F12),  _______,  _______,  RGB_TOG,
	/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┤ */
		 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       RGB_MOD,       RGB_SAI,
	/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┤ */
		 _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                 RGB_VAI,
	/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬           ├─────────┤ */
		 _______,          _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET,  _______,  _______,  TO(_NUM),   RGB_HUI,
	/* ├───────────┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴─────────┴─┬─────────┼─────────┤ */
		 _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MEDIA_SELECT,  KC_VOLU,  KC_MPLY,
	/* ├───────────┼─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┼─────────┤ */
		 _______,    _______,    _______,                                _______,                            _______, _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT
	/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
    ),

	[_NUM] = LAYOUT_75_iso(
	/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
		 TO(_BAS), _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,
	/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┤ */
		 KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_NO,    KC_NO,     KC_NO,       KC_NO,          KC_NO,
	/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┤ */
		    KC_NO,       KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,   KC_KP_MINUS,KC_KP_4, KC_KP_5,  KC_KP_6, KC_KP_PLUS,KC_NO,     KC_NO,                  KC_NO,
	/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬           ├─────────┤ */
		 KC_NO,            KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_KP_SLASH,KC_KP_1, KC_KP_2,KC_KP_3, KC_KP_ASTERISK,KC_NO, KC_NO,   KC_KP_ENTER, KC_NO,
	/* ├───────────┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴─────────┴─┬─────────┼─────────┤ */
		 KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_KP_0,  KC_KP_DOT, KC_KP_DOT,  KC_NO,     KC_NO,            KC_NO,    KC_NO,
	/* ├───────────┼─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┼─────────┤ */
		 KC_NO,      KC_NO,       KC_NO,                                KC_NO,                               KC_NO,    TO(_BAS),  KC_NO,  KC_NO,     KC_NO,    KC_NO
	/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
    )
};

static bool mayusculas = false;
static bool luces_enabled = false;
//Lee el estado el led de mayuculas y lo almacena en la variable mayusculas
void led_set_kb(uint8_t usb_led) {
  mayusculas = !(usb_led & (1 << USB_LED_CAPS_LOCK));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CAPS:
        if (record->event.pressed) {
            if (mayusculas) {
                luces_enabled = rgblight_is_enabled();
                rgblight_enable();
                rgblight_mode(RGBLIGHT_MODE_SNAKE+3);
            } else {
                rgblight_mode(RGBLIGHT_MODE_BREATHING + 1);
                if(!luces_enabled){
                    rgblight_disable();
                }
            }
        }

      break;
  }
  return true;
}
