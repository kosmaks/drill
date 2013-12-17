#include "engine/core/app.h"
#include "dxinput.h"

using namespace drill;

void dxinput::defined() {
  router = REQUIRE(context).get_info<winapi_router_t>();

  router->keydown = [this] (WPARAM w, LPARAM l) { keydown(w, l); };
  router->keyup = [this] (WPARAM w, LPARAM l) { keyup(w, l); };
  router->mouse = [this] (int b, int s) { mouse(b, s); };
}

void dxinput::keydown(WPARAM w, LPARAM l) {
  set_key(w);
  on_keydown.trigger();
}

void dxinput::keyup(WPARAM w, LPARAM l) {
  set_key(w);
  on_keyup.trigger();
}

void dxinput::mouse(int btn, int state) {
  LOG_DEBUG("Click");
  _mouse_button = MOUSE_BUTTON_LEFT;
  if (!btn && state) {
      on_mousedown.trigger();
  } else if (!btn && !state) {
      on_mouseup.trigger();
  } 

  _mouse_button = MOUSE_BUTTON_RIGHT;
  if (btn && state) {
      on_mousedown.trigger();
  } else if (btn && !state) {
      on_mouseup.trigger();
  } 
}

void dxinput::set_key(uint32_t key) {
  _key = key;
  switch (_key) {
    case VK_UP: _key = INPUT_KEY_UP; break;
    case VK_DOWN: _key = INPUT_KEY_DOWN; break;
    case VK_LEFT: _key = INPUT_KEY_LEFT; break;
    case VK_RIGHT: _key = INPUT_KEY_RIGHT; break;
  }
}
