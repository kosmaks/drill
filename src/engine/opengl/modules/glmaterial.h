#pragma once

#include "engine/virtual/modules/material.h"
#include "glshader.h"

namespace drill {
  class glmaterial : public glshader, public material {
  public:
    void link_to(linker *l) { glshader::link_to(l); }
    void defined();
    void ready();
    material& use_texture(const texture &texture);
    material& color(const vector4_t &color);

  private:
    vector4_t _color;
    uint32_t tex_id;
  };
}
