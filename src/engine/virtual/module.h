#pragma once

#include "engine/core/app.h"
#include "engine/core/platform.h"
#include "linker.h"

namespace drill {
  class linker;
  class module : public dependency {
  public:
    virtual ~module() {}
    virtual void init() = 0;
    virtual void link_to(linker *l) = 0;
    virtual void ready() {};
  };
}
