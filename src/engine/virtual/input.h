#pragma once

#include "engine/core/events.h"
#include "engine/core/platform.h"

namespace drill {
  class input : public dependency {
  public:
    input();
    virtual ~input();

    event on_keypress;
    event on_keyup;
    event on_keydown;
    event on_mousemove;
    event on_mousedown;
    event on_mouseup;
  };
}
