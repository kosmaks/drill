#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glcommon.h"

#define GL_WAITING 0
#define GL_READY 1

int gl_status = GL_WAITING;

bool drill::glinit() {
  if (gl_status > GL_WAITING) return false;
  LOG_INFO("Initializing OpenGL");
  return true;
}
