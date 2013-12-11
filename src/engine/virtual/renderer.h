#pragma once

#include <string>
#include "engine/core/events.h"
#include "engine/core/platform.h"
#include "engine/world/scene.h"
#include "engine/virtual/service.h"
#include "engine/virtual/context.h"
#include "engine/virtual/module_source.h"

namespace drill {
  class renderer : public dependency, public service {
  public:
    renderer();
    virtual ~renderer();
    void defined();

    void update(const timeinfo_t &timeinfo);

    void use_scene(scene &new_scene);

  protected:
    scene *current_scene;
    context *current_context;
  };
}
