#pragma once

#include "engine/core/platform.h"
#include "module.h"

namespace drill {
  class module;

  class c_program {
  public:
    virtual ~c_program() {}
    virtual void use() = 0;
  };

  class linker : public dependency {
  public:
    virtual ~linker() {};
    virtual linker& begin() = 0;
    virtual linker& include(module &m) = 0;
    virtual c_program* create() = 0;
  };
}
