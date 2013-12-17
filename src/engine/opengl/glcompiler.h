#pragma once

#include <GL/glew.h>
#include "engine/virtual/compiler.h"

namespace drill {
  class glc_object : public c_object { 
  public: 
    void render(); 
    void free() {}
    uint32_t vao;
    uint32_t triangles, triangles_count;
    uint32_t points, points_count;
  private:
    inline void use_buffer(uint32_t id, uint32_t count, GLenum mode);
  };

  class glcompiler : public compiler {
  public: 
    virtual ~glcompiler();
    c_object* compile(object &obj);
    void defined() {}

  private:
    std::map<void*, glc_object*> _pool;
    uint32_t generate_vbo(vertex_t *pointer, uint32_t size);
  };
}
