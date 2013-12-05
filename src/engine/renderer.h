#pragma once

#include "scene.h"

namespace drill {
  class Renderer {
  public:
    Renderer();
    virtual ~Renderer();

    virtual void init_window(const std::string &title) = 0;
    virtual void set_fullscreen_enabled(bool enabled) = 0;

    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    void use_scene(Scene scene);

  private:
    Scene *current_scene;
  };
}
