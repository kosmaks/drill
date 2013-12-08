#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glbridge_object.h"

using namespace drill;

void glbridge_object::compile() {
  LOG_DEBUG("Compiling GL object");
}

void glbridge_object::draw() {
  glBegin(GL_TRIANGLES);
  for (uint32_t i = 0; i < current_target->triangles.count; ++i) {
    vector3_t &vertex = current_target->triangles.vertices[i];
    glVertex3f(vertex.x, vertex.y, vertex.z);
  }
  glEnd();
}
