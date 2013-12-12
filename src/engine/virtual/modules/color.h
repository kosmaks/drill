#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"

namespace drill {
  class color : public module {
  public:
    vector4_t value;

    color& set(coord_t r, coord_t g, coord_t b, coord_t a) {
      value = { r, g, b, a };
      return *this;
    }

    color& red(coord_t r) { value.x = r; return *this; }
    color& green(coord_t g) { value.y = g; return *this; }
    color& blue(coord_t b) { value.z = b; return *this; }
    color& alpha(coord_t a) { value.w = a; return *this; }
  };
}
