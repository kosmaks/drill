#include "engine/core/app.h"
#include "object.h"

using namespace drill;

object::object() {
  _triangles = nullptr;
  _triangles_count = 0;
  _points = nullptr;
  _points_count = 0;
  _transfered_ownership = false;
}

object::object(uint32_t t_count, uint32_t p_count) {
  _triangles = nullptr;
  _triangles = new vertex_t[t_count];
  _triangles_count = t_count;
  LOG_DEBUG("Triangles count: " << t_count);

  _points = nullptr;
  _points = new vertex_t[p_count];
  _points_count = p_count;
  LOG_DEBUG("Points count: " << p_count);

  _transfered_ownership = false;
}

void object::transfer_ownership() {
  _transfered_ownership = true;
}

object::~object() {
  if (!_transfered_ownership) { 
    if (_triangles != nullptr) delete _triangles; 
    if (_points != nullptr) delete _points; 
  }
}
