#pragma once

#include "engine/virtual/linker.h"

namespace drill {
  class gllinker : public linker {
  public:
    linker& begin();
    linker& include(module &m);
    linker& end();
    linker& use();

    linker& update(module &m);
    void defined() {}

    uint32_t c_shader_program();

  private:
    uint32_t shader_program;
  };
}

