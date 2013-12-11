#pragma once

#include "engine/core/app.h"
#include "engine/core/types.h"
#include "engine/virtual/drawable.h"
#include "engine/virtual/module_source.h"

namespace drill {
  class camera : public drawable {
  public:
    camera(module_source *msource);
    void draw();

  protected:
    module_source *_msource;
    
  private:
    camera_controller *_controller;
  };
}
