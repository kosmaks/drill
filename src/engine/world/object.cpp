#include "engine/core/app.h"
#include "object.h"

using namespace drill;

object::object() {
  _triangles = nullptr;
  _triangles_count = 0;
  _transfered_ownership = false;
}

object::object(uint32_t t_count) {
  _triangles = nullptr;
  _triangles = new vertex_t[t_count];
  _triangles_count = t_count;
  _transfered_ownership = false;
  LOG_DEBUG("Triangles count: " << t_count);
}

vertex_t* object::transfer_ownership() {
  _transfered_ownership = true;
  return _triangles;
}

object::~object() {
  if (_triangles != nullptr && !_transfered_ownership) { 
    delete _triangles; 
  }
}
