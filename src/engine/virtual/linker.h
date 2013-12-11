#pragma once

#include "engine/core/platform.h"
#include "module.h"

namespace drill {
  class module;
  class linker : public dependency {
  public:
    virtual ~linker() {};
    virtual linker& begin() = 0;
    virtual linker& include(module &m) = 0;
    virtual linker& end() = 0;
    virtual linker& use() = 0;
    virtual linker& operator<<(module &m) = 0;
  };
}
