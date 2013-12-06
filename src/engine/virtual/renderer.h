#pragma once

#include <string>
#include "engine/core/events.h"
#include "engine/virtual/scene.h"

namespace drill {
  class renderer {
  public:
    renderer();
    virtual ~renderer();
    void use_scene(scene *new_scene);

  private:
    scene *current_scene;
  };
}
