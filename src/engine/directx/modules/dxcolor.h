#pragma once

#include "engine/virtual/modules/color.h"
#include "dxshader.h"

namespace drill {
  class dxcolor : public dxshader, public color {
  public:
    void init();
    void link_to(linker *l) { _link_to(l); }
    void defined();
  };
}
