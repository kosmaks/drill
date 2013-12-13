#pragma once

#include "engine/core/types.h"

namespace drill {
  class object {
  public:
    object(uint32_t t_count);
    object();
    ~object();

    inline vertex_t* get_triangles() { return _triangles; }
    inline vertex_t* get_triangles(uint32_t x) { return &_triangles[x]; }
    inline uint32_t get_triangles_count() { return _triangles_count; }

  private:
    vertex_t *_triangles;
    uint32_t _triangles_count;
  };
}
