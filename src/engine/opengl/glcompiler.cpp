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

  glGenVertexArrays(1, &r->vao);
  glBindVertexArray(r->vao);

  r->triangles = generate_vbo(obj.get_triangles(), 
                   sizeof(vertex_t) * obj.get_triangles_count());
  r->triangles_count = obj.get_triangles_count();

  r->points = generate_vbo(obj.get_points(), 
                   sizeof(vertex_t) * obj.get_points_count());
  r->points_count = obj.get_points_count();


  return r;
}

void glc_object::render() {
  use_buffer(triangles, triangles_count, GL_TRIANGLES);
  use_buffer(points, points_count, GL_POINTS);
}

void glc_object::use_buffer(uint32_t id, uint32_t count, GLenum mode) {
  if (count > 0) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawArrays(mode, 0, count);
  }
}

uint32_t glcompiler::generate_vbo(vertex_t *pointer, uint32_t size) {
  uint32_t vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, pointer, GL_STATIC_DRAW);
  return vbo;
}
