#pragma once

#include "engine/core/events.h"
#include "engine/virtual/service.h"
#include "scene.h"

namespace drill {
  class view : public service {
  public:
    view() {}

    scene &get_scene() { return *c_scene; }
    void set_scene(scene &s);

  protected:
    // helpers
    template<class T> T* require() { return &get_scene().c_platform.require<T>(); }
    template<class T> T* include() { return &get_scene().c_platform.include<T>(); }

  private:
    event::callback_t callback;   
    scene *c_scene;
  };
}
