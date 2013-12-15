#pragma once

#include "engine/virtual/modules/color.h"
#include "glshader.h"

namespace drill {
  class glcolor : public glshader, public color {
  public:
    void link_to(linker *l) { glshader::link_to(l); }
    void flush(c_program *p) { glshader::flush(p); }
    void flush();
    void defined();
  };
}

