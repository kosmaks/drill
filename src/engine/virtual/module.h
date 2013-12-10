#pragma once

#include "engine/core/app.h"

namespace drill {
  class module {
  public:
    virtual ~module() { }
    virtual void link() = 0;
  };
}
