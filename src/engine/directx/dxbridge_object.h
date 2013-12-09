#pragma once

#include "engine/world/object.h"
#include "engine/virtual/bridge.h"

namespace drill {
  class dxbridge_object : public bridge<object> {
  public:
    dxbridge_object(object &target) : bridge(target) {} 
    void compile();
    void draw();
  };
}
