#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glinput.h"

using namespace drill;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  glcontext::glfw_router_t *router = 
    (glcontext::glfw_router_t*)glfwGetWindowUserPointer(window);
  router->keyfun(window, key, scancode, action, mods);
}

void glinput::defined() {
  router = REQUIRE(context).get_info<glcontext::glfw_router_t>();

  router->keyfun = [this] (GLFWwindow *window, int key, int scancode, 
                           int action, int mods) { keyfun(key, action); };

  glfwSetKeyCallback(router->window, key_callback);
}

void glinput::keyfun(int32_t key, int action) {
  _key = key;
  if (action == GLFW_RELEASE) {
    on_keyup.trigger();
  } else {
    on_keydown.trigger();
  }
}
