#pragma once

#include "engine/virtual/linker.h"

namespace drill {
  class glc_program : public c_program {
  public:
    void use();
    uint32_t shader_program;
  };

  class gllinker : public linker {
  public:
    void defined() {}

    linker& begin();
    linker& include(module &m);

    c_program* create();

    uint32_t c_shader_program() { return shader_program; }

  private:
    uint32_t shader_program;
  };
}

