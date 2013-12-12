#pragma once

#include "engine/virtual/compiler.h"

namespace drill {
  class glc_object : public c_object { 
    public: 
      void render(); 
      uint32_t vertices, count;
  };

  class glcompiler : public compiler {
  public: 
    virtual ~glcompiler();
    c_object* compile(object &obj);
    void defined() {}

  private:
    std::map<void*, glc_object*> _pool;
    uint32_t generate_vbo(void *pointer, uint32_t size, uint32_t vertex_size);
  };
}
