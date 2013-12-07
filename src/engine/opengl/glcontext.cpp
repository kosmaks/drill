#include "engine/core/app.h"
#include "glcommon.h"
#include "glcontext.h"

using namespace drill;

void glfw_error_callback(int error, const char* description) {
  LOG_ERROR("GLFW Error #" << error << ": " << description);
}

glcontext::glcontext(const std::string &title, int width, int height) {
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
}

void glcontext::swap_buffers() {
  glfwSwapBuffers(_window);
  glfwPollEvents();
}
