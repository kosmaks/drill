#pragma once

#include "engine/core/app.h"
#include "engine/core/types.h"
#include "engine/virtual/drawable.h"
#include "engine/virtual/module_source.h"
#include "engine/virtual/modules/object_compiler.h"

namespace drill {
  class object : public drawable {
  public:
    object(module_source *msource);

    void draw();
    void compile();

    coordset_t triangles;

  protected:
    module_source *_msource;
    
  private:
    object_compiler *_compiler;
    transform       *_transform;
    compiled_object *_renderer;
  };
}
