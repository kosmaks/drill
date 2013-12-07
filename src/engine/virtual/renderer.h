#pragma once

#include <string>
#include "engine/core/events.h"
#include "engine/world/scene.h"
#include "engine/virtual/service.h"
#include "engine/virtual/context.h"

namespace drill {
  class renderer : public service {
  public:
    renderer(context &cont);
    virtual ~renderer();

    void init();
    void update();

    void use_scene(scene &new_scene);

  protected:
    scene *current_scene;
    context *current_context;

  private:
    scene empty_scene; 
  };
}
