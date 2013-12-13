#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"
#include "engine/world/texture.h"

namespace drill {
  class material : public module {
  public:
    virtual material& use_texture(const texture &texture) = 0;
    virtual material& color(const vector4_t &color) = 0;
  };
}
