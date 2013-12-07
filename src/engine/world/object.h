#pragma once

#include "engine/core/types.h"
#include "engine/virtual/compiler.h"

namespace drill {
  class obejct {
  public:
    const vector3_t *vertices();
    const vector3_t *normals();
    const vector2_t *textures();

    bool needs_compilation();
    void compile_with(const copmpiler &comiler);

  private:
    vector3_t *vertices;
    vector3_t *normals;
    vector2_t *textures;
    uint32_t* faces;

  };
}
