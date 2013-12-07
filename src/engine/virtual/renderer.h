#pragma once

#include <string>
#include "engine/core/events.h"
#include "engine/virtual/scene.h"
#include "engine/virtual/service.h"

namespace drill {
  class renderer : public service {
  public:
    renderer();
    virtual ~renderer();

    void use_scene(scene *new_scene);

  private:
    scene *current_scene;
  };
}
