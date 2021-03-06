#pragma once

#include <map>
#include "engine/virtual/modules/dilate.h"
#include "glshader.h"

namespace drill {
  class gldilate : public glshader, public dilate {
  public:
    ~gldilate() {}
    void flush(c_program *p) { glshader::flush(p); }
    void link_to(linker *l);
    void defined();
    void flush() {}
  };
}
