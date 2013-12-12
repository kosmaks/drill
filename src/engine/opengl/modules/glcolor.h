#pragma once

#include "engine/virtual/modules/color.h"
#include "glshader.h"

namespace drill {
  class glcolor : public glshader, public color {
  public:
    void init();
    void link_to(linker *l) { glshader::link_to(l); }
    void ready();
    void defined() {}
  };
}

