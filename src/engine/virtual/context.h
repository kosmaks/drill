#pragma once

#include <string>
#include "engine/core/events.h"

namespace drill {
  class context {
  public:
    virtual ~context() {}
    virtual void load() = 0;
    virtual void swap_buffers() = 0;

    event resize;
  };
}
