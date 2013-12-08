#pragma once

#include "engine/core/types.h"
#include "engine/virtual/drawable.h"
#include "engine/virtual/bridge.h"

namespace drill {
  class object : public drawable {
  public:
    vector3_t position = { 0, 0, 0 };
    vector3_t rotation = { 0, 0, 0 };
    vector3_t scale    = { 1, 1, 1 };

    void draw() { if (drawer) drawer->draw(*this); }
    bridge<object> *drawer;
  };
}
