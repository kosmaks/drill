#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glcommon.h"

#define GL_WAITING 0
#define GL_READY 1

int gl_status = GL_WAITING;
char gl_log[4096];

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

uint32_t drill::glcompile_shader(const std::string &source, glshader_t type) {
  LOG_DEBUG("Compiling GLSL shader");

  int actual_length;
  const char *source_c = source.c_str();

  uint32_t shader = glCreateShader((type == GL_VS) ? GL_VERTEX_SHADER
                                                   : GL_FRAGMENT_SHADER);
  glShaderSource(shader, 1, &source_c, NULL);
  glCompileShader(shader);
  glGetShaderInfoLog(shader, 4095, &actual_length, gl_log);

  if (actual_length > 0) {
    LOG_ERROR("Error compiling shader: " << gl_log);
    throw -1;
  }

  return shader;
}
