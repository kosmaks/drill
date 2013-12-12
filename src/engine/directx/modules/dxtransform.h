#pragma once

#include "engine/virtual/modules/transform.h"
#include "dxshader.h"

namespace drill {
  class dxtransform : public dxshader, public transform {
  public:
    void init();
    void link_to(linker *l) { _link_to(l); }
    void defined();
  };
}
