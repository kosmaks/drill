#pragma once

#include "../glmodule_source.h"
#include "engine/virtual/modules/object_compiler.h"

namespace drill {
  class globject_compiler : public object_compiler {
  public:
    void link() {}
    compiled_object* compile(coordset_t *obj);

  private:
    uint32_t generate_vbo(void *pointer, uint32_t size);
  };

  class glcompiled_object : public compiled_object {
  public:
    glcompiled_object(uint32_t vertices, uint32_t count);
    void render();
  private:
    uint32_t _vertices;
    uint32_t _count;
  };
}
