#pragma once

#include <types.h>

typedef enum
{
  KB_NONE,
  KB_PRESS,
  KB_RELEASE
} kb_state;

typedef enum
{
  /* No key */
  KEY_NONE = 0,

  /* Control / system */
  KEY_ESC,
  KEY_TAB,
  KEY_CAPS_LOCK,
  KEY_LSHIFT,
  KEY_RSHIFT,
  KEY_LCTRL,
  KEY_RCTRL,
  KEY_LALT,
  KEY_RALT,
  KEY_LGUI,
  KEY_RGUI,
  KEY_MENU,

  /* Function keys */
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,

  /* Alphanumeric */
  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,

  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,

  /* Punctuation */
  KEY_GRAVE,
  KEY_MINUS,
  KEY_EQUALS,
  KEY_LBRACKET,
  KEY_RBRACKET,
  KEY_BACKSLASH,
  KEY_SEMICOLON,
  KEY_APOSTROPHE,
  KEY_COMMA,
  KEY_PERIOD,
  KEY_SLASH,

  /* Main keyboard */
  KEY_BACKSPACE,
  KEY_ENTER,
  KEY_SPACE,

  /* Navigation */
  KEY_INSERT,
  KEY_DELETE,
  KEY_HOME,
  KEY_END,
  KEY_PAGE_UP,
  KEY_PAGE_DOWN,

  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,

  /* Lock keys */
  KEY_NUM_LOCK,
  KEY_SCROLL_LOCK,

  /* Numpad */
  KEY_NUMPAD_0,
  KEY_NUMPAD_1,
  KEY_NUMPAD_2,
  KEY_NUMPAD_3,
  KEY_NUMPAD_4,
  KEY_NUMPAD_5,
  KEY_NUMPAD_6,
  KEY_NUMPAD_7,
  KEY_NUMPAD_8,
  KEY_NUMPAD_9,

  KEY_NUMPAD_DECIMAL,
  KEY_NUMPAD_DIVIDE,
  KEY_NUMPAD_MULTIPLY,
  KEY_NUMPAD_MINUS,
  KEY_NUMPAD_PLUS,
  KEY_NUMPAD_ENTER,

  /* Print / pause */
  KEY_PRINT_SCREEN,
  KEY_PAUSE,

  /* International / extra keys */
  KEY_NONUS_BACKSLASH,

  KEY_COUNT
} kb_key;

typedef struct
{
  uint8    Scancode;
  kb_state State;
  char     Ascii;
  kb_key   Key;
} kb_input;

void     keyboard_read(kb_input *Input);
kb_state keyboard_state(kb_key Key);
