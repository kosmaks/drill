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
  router.window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwSetWindowUserPointer(router.window, &router);

  if (!router.window) {
    LOG_ERROR("Unable to create GLFW context");
    return;
  }

}

void glcontext::load() {
  glfwMakeContextCurrent(router.window);
  LOG_DEBUG("OpenGL context is set");
}

void glcontext::swap_buffers() {
  glfwSwapBuffers(router.window);
  glfwPollEvents();
}

void glcontext::clear_screen() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void *glcontext::info(size_t hash) {
  if (hash == typeid(glfw_router_t).hash_code()) {
    return &router;
  } else {
    return nullptr;
  }
}
