#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glbridge_object.h"

using namespace drill;

void glbridge_object::compile() {
  LOG_DEBUG("Compiling GL object");
  glGenBuffersARB(1, &vbo);
  glBindBufferARB(GL_ARRAY_BUFFER, vbo);
  glBufferDataARB(GL_ARRAY_BUFFER, 
                  sizeof(vector3_t) * current_target->triangles.count, 
                  current_target->triangles.vertices, 
                  GL_STATIC_DRAW);
  glVertexPointer(3, GL_FLOAT, 0, NULL);
}

void glbridge_object::draw() {
  glBindBufferARB(GL_ARRAY_BUFFER, vbo);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLES, 0, current_target->triangles.count);
}
