#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"

namespace drill {
  class color : public module {
  public:
    vector3_t value;

    color& set(coord_t r, coord_t g, coord_t b) {
      value = { r, g, b };
      return *this;
    }

    color& red(coord_t r) { value.x = r; return *this; }
    color& green(coord_t g) { value.y = g; return *this; }
    color& blue(coord_t b) { value.z = b; return *this; }
  };
}
