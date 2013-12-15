#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"
#include "engine/world/texture.h"

namespace drill {
  class c_texture { 
  public:
    virtual ~c_texture() {}
    virtual void use() = 0;
  };

  class material : public module {
  public:
    virtual ~material() {}
    virtual c_texture* compile_texture(texture &texture) = 0;
    virtual material& use_texture(c_texture *c_texture) = 0;
    virtual material& color(const vector4_t &color) = 0;
  };
}
