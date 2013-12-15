#pragma once

#include <map>
#include "engine/core/types.h"
#include "engine/core/events.h"
#include "engine/core/platform.h"

#define INPUT_KEY_UP 265
#define INPUT_KEY_DOWN 264
#define INPUT_KEY_LEFT 263
#define INPUT_KEY_RIGHT 262

namespace drill {
  class input : public dependency {
  public:
    typedef enum {
      MOUSE_BUTTON_LEFT,
      MOUSE_BUTTON_RIGHT,
    } mouse_button_t;

    virtual ~input() {}

    virtual int32_t get_key() = 0;
    virtual mouse_button_t get_mouse_button() = 0;
    virtual uint32_t get_mouse_x() = 0;
    virtual uint32_t get_mouse_y() = 0;

    event on_keyup;
    event on_keydown;
    event on_mousemove;
    event on_mousedown;
    event on_mouseup;
  };
}
