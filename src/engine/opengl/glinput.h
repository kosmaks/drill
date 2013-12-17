#pragma once

#include "engine/virtual/input.h"
#include "glcontext.h"

namespace drill {
  class glinput : public input {
  public:
    void defined();
    void update(const timeinfo_t &time);

    int32_t get_key() { return _key; }
    mouse_button_t get_mouse_button() { return _mouse_button; }
    uint32_t get_mouse_x() { return _mouse_x; }
    uint32_t get_mouse_y() { return _mouse_y; }


  private:
    glcontext::glfw_router_t *router;

    void keyfun(int32_t key, int32_t action);
    void mousebutton(int32_t button, int32_t action);

    int32_t _key;
    uint32_t _mouse_x, _mouse_y;
    mouse_button_t _mouse_button;
  };
}
