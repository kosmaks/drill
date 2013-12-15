#pragma once

#include <functional>
#include <GLFW/glfw3.h>
#include "engine/virtual/context.h"

namespace drill {
  class glcontext : public context {
  public:
    typedef struct {
      GLFWwindow *window;
      std::function<void(GLFWwindow*, int, int, int)> mousebuttonfun;
      std::function<void(GLFWwindow*, double, double)> cursorposfun;
      std::function<void(GLFWwindow*, double, double)> scrollfun;
      std::function<void(GLFWwindow*, int, int, int, int)> keyfun;
      std::function<void(GLFWwindow*, int, int)> windowposfun;
      std::function<void(GLFWwindow*)> windowclosefun;
    } glfw_router_t;

    glcontext(const std::string &title = "GLFW Context", 
              int width=640, 
              int height=480);
    void load();
    void swap_buffers();
    void clear_screen();
    void defined() {}
    inline uint32_t get_width() { return _width; }
    inline uint32_t get_height() { return _height; }

    virtual void* info(size_t hash);

  private:
    glfw_router_t router;
    uint32_t _width, _height;
  };
}
