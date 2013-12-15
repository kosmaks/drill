#pragma once

#include "engine/virtual/linker.h"
#include "dxcontext.h"

namespace drill {
  class dxc_program : public c_program {
  public:
    void use();
    dxhandle_t *handle;
  };

  class dxlinker : public linker {
  public:
    void defined();

    linker& begin();
    linker& include(module &m);

    c_program* create();

  private:
    dxhandle_t *handle;
  };
}

