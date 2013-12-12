#pragma once

#include "engine/virtual/modules/transform.h"
#include "glshader.h"

namespace drill {
  class gltransform : public glshader, public transform {
  public:
    void init();
    void link_to(linker *l) { glshader::link_to(l); }
    void defined() {}
  };
}
