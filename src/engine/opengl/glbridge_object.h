#pragma once

#include "engine/world/object.h"
#include "engine/virtual/bridge.h"

namespace drill {
  class glbridge_object : public bridge<object> {
  public:
    void compile(object &obj);
    void draw(object &obj);
  };
}
