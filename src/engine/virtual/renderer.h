#pragma once

#include <string>
#include "engine/core/events.h"
#include "engine/virtual/scene.h"
#include "engine/virtual/service.h"
#include "engine/virtual/context.h"

namespace drill {
  class renderer : public service {
  public:
    renderer(context &cont);
    virtual ~renderer();

    void init();

    void use_scene(scene *new_scene);

  protected:
    scene *current_scene;
    context *current_context;
  };
}
