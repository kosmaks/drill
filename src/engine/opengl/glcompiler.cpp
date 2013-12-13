#include <GL/glew.h>
#include <algorithm>
#include "engine/core/app.h"
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

  LOG_INFO("Drawing " << obj.get_triangles_count() << " vertices");
  r->vertices = generate_vbo(obj.get_triangles(), 
                sizeof(vertex_t) * obj.get_triangles_count());
  r->count = obj.get_triangles_count();

  return r;
}

void glc_object::render() {
  glBindBuffer(GL_ARRAY_BUFFER, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glDrawArrays(GL_TRIANGLES, 0, count);
}

uint32_t glcompiler::generate_vbo(vertex_t *pointer, uint32_t size) {
  uint32_t vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, pointer, GL_STATIC_DRAW);
  glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), (void*)0);
  glNormalPointer(GL_FLOAT, sizeof(vertex_t), (void*)(5 * sizeof(float)));
  return vbo;
}
