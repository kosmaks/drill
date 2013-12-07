#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glcommon.h"

#define GL_WAITING 0
#define GL_READY 1

int gl_status = GL_WAITING;

bool drill::glinit() {
  if (gl_status > GL_WAITING) return true;

  LOG_INFO("Initializing OpenGL");

  if (!glfwInit()) {
    LOG_ERROR("Unable to initialize GLFW");
    return false;
  }

  gl_status = GL_READY;
  return true;
}
