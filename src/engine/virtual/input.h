#pragma once

#include "engine/core/events.h"
#include "engine/virtual/service.h"

namespace drill {
  class input : public service {
  public:
    input();
    virtual ~input();

    event keypress;
    event keyup;
    event keydown;
    event mousemove;
    event mousedown;
    event mouseup;
  };
}
