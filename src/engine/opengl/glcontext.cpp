#include "engine/core/app.h"
#include "glcommon.h"
#include "glcontext.h"

using namespace drill;

void glfw_error_callback(int error, const char* description) {
  LOG_ERROR("GLFW Error #" << error << ": " << description);
}

glcontext::glcontext(const std::string &title, int width, int height) {
  _width = width;
  _height = height;

  glinit(); 
  glfwSetErrorCallback(glfw_error_callback);
  _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

  if (!_window) {
    LOG_ERROR("Unable to create GLFW context");
    return;
  }

}

void glcontext::load() {
  glfwMakeContextCurrent(_window);
  LOG_DEBUG("OpenGL context is set");
}

void glcontext::swap_buffers() {
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void glcontext::clear_screen() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
