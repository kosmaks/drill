#pragma once

#include "engine/core/types.h"

namespace drill {
  class object {
  public:
    object(uint32_t t_count, uint32_t p_count = 0);
    object();
    ~object();

    inline vertex_t* get_triangles()           { return _triangles; }
    inline vertex_t* get_triangles(uint32_t x) { return &_triangles[x]; }
    inline uint32_t  get_triangles_count()     { return _triangles_count; }

    inline vertex_t* get_points()           { return _points; }
    inline vertex_t* get_points(uint32_t x) { return &_points[x]; }
    inline uint32_t  get_points_count()     { return _points_count; }

    void transfer_ownership();

  private:
    vertex_t *_triangles;
    uint32_t _triangles_count;
    vertex_t *_points;
    uint32_t _points_count;
    bool _transfered_ownership;
  };
}
