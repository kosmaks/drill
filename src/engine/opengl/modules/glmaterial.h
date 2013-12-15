#pragma once

#include <map>
#include "engine/virtual/modules/material.h"
#include "glshader.h"

namespace drill {
  class glc_texture : public c_texture {
  public:
    glc_texture() {}
    glc_texture(uint32_t tex_id);
    void use();
  private:
    uint32_t _tex_id; 
  };

  class glmaterial : public glshader, public material {
  public:
    ~glmaterial();
    void link_to(linker *l) { glshader::link_to(l); }
    void flush(c_program *p) { glshader::flush(p); }
    void defined();
    void flush();

    c_texture* compile_texture(texture &texture);
    material& use_texture(c_texture *c_texture);
    material& color(const vector4_t &color);

  private:
    vector4_t _color;
    std::map<void*, glc_texture*> _pool;
  };
}
