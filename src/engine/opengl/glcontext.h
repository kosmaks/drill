#pragma once

#include <GLFW/glfw3.h>
#include "engine/virtual/context.h"

namespace drill {
  class glcontext : public context {
  public:
    glcontext(const std::string &title = "GLFW Context", 
              int width=640, 
              int height=480);
    void load();
    void swap_buffers();
    void clear_screen();
    void defined() {}
    inline uint32_t get_width() { return _width; }
    inline uint32_t get_height() { return _height; }

    virtual void* info(size_t hash) { return nullptr; }

  private:
    GLFWwindow *_window;
    uint32_t _width, _height;
  };
}
