#pragma once

#include "engine/virtual/input.h"
#include "dxcontext.h"

namespace drill {
  class dxinput : public input {
  public:
    void defined();
    void update(const timeinfo_t &time);

    int32_t get_key() { return _key; }
    mouse_button_t get_mouse_button() { return _mouse_button; }
    uint32_t get_mouse_x() { return _mouse_x; }
    uint32_t get_mouse_y() { return _mouse_y; }


  private:
    winapi_router_t *router;

    void keydown(WPARAM w, LPARAM l);
    void keyup(WPARAM w, LPARAM l);
    void mouse(int btn, int state);

    void set_key(uint32_t key);

    int32_t _key;
    uint32_t _mouse_x, _mouse_y;
    mouse_button_t _mouse_button;
  };
}
