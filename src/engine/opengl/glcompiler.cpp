#include <GL/glew.h>
#include <algorithm>
#include "glcompiler.h"

using namespace drill;

glcompiler::~glcompiler() {
  for (std::pair<void*, glc_object*> pair : _pool) {
    delete pair.second; 
  }
}

c_object* glcompiler::compile(object &obj) {
  glc_object *r = _pool[&obj];
  if (r == nullptr) { _pool[&obj] = r = new glc_object(); }

  r->vertices = generate_vbo(obj.triangles.vertices, 
                sizeof(vector3_t) * obj.triangles.count,
                3);
  r->count = obj.triangles.count;

  return r;
}

void glc_object::render() {
  glBindBuffer(GL_ARRAY_BUFFER, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLES, 0, count);
}

uint32_t glcompiler::generate_vbo(void *pointer, uint32_t size, uint32_t vertex_size) {
  uint32_t vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, pointer, GL_STATIC_DRAW);
  glVertexPointer(vertex_size, GL_FLOAT, 0, NULL);
  return vbo;
}
