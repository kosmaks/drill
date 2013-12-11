#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "globject_compiler.h"

using namespace drill;

compiled_object* globject_compiler::compile(coordset_t *triangles) {
  LOG_INFO("Compiling OpenGL object");

  uint32_t vertices = generate_vbo(triangles->vertices, 
                                   sizeof(vector3_t) * 
                                     triangles->count);
  glVertexPointer(3, GL_FLOAT, 0, NULL);

  glcompiled_object *res = new glcompiled_object(vertices, triangles->count);
  return res;
}

glcompiled_object::glcompiled_object(uint32_t vertices, uint32_t count) : compiled_object() {
  _vertices = vertices;
  _count = count;
}

void glcompiled_object::render() {
  glBindBuffer(GL_ARRAY_BUFFER, _vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLES, 0, _count);
}

uint32_t globject_compiler::generate_vbo(void *pointer, uint32_t size) {
  uint32_t vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, pointer, GL_STATIC_DRAW);
  return vbo;
}
