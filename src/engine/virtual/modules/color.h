#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"

namespace drill {
  class color : public module {
  public:
    color() : value({ 0.0, 0.0, 0.0, 0.0 }) {}
    vector4_t value;

    inline color& set(vector4_t v) {
      value = v;
      return *this;
    }

    inline color& red(coord_t r) { value.x = r; return *this; }
    inline color& green(coord_t g) { value.y = g; return *this; }
    inline color& blue(coord_t b) { value.z = b; return *this; }
    inline color& alpha(coord_t a) { value.w = a; return *this; }
  };
}
