#pragma once

#include "engine/virtual/modules/transform.h"
#include "../glmodule_source.h"

namespace drill {
  class gltransform : public transform {
  public:
    gltransform(glmodule_source *source);
    void link();
    void ready();
  private:
    glmodule_source *_source;
    uint32_t vs, fs;
  };
}
