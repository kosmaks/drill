#pragma once

#include "engine/world/object.h"
#include "engine/virtual/bridge.h"

namespace drill {
  class glbridge_object : public bridge<object> {
  public:
    glbridge_object(object &target) : bridge(target) {} 
    void compile();
    void draw();
  private:
    uint32_t vertices;

    uint32_t generate_vbo(void *pointer, uint32_t count);
  };
}
