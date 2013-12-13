#include "engine/core/app.h"
#include "object.h"

using namespace drill;

object::object() {
  _triangles = nullptr;
  _triangles_count = 0;
}

object::object(uint32_t t_count) {
  _triangles = new vertex_t[t_count];
  _triangles_count = t_count;
  LOG_INFO("Triangles count: " << t_count);
}

object::~object() {
  delete _triangles;
}
