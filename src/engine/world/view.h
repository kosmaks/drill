#pragma once

#include "engine/virtual/service.h"
#include "engine/core/platform.h"

namespace drill {
  class view : public service {
  public:
    view(platform &plat) : active(true),
                           p(plat) {}
    bool active;

  protected:
    platform &p;
  };
}
