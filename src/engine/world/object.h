#pragma once

#include "engine/core/app.h"
#include "engine/core/types.h"
#include "engine/virtual/drawable.h"
#include "engine/virtual/bridge.h"

namespace drill {
  class object : public drawable {
  public:
    object() {
      position = { 0, 0, 0 };
      rotation = { 0, 0, 0 };
      scale = { 1, 1, 1 };
      color = { 1.0f, 0.0f, 0.0f };
    }
    vector3_t position;
    vector3_t rotation;
    vector3_t scale;

    vector3_t color;

    void draw() { if (drawer) drawer->draw(); }
    bridge<object> *drawer;

    coordset_t triangles;
  };
}
