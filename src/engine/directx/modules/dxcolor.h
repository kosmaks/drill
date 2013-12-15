#pragma once

#include "engine/virtual/modules/color.h"
#include "dxshader.h"

namespace drill {
  class dxcolor : public dxshader, public color {
  public:
    void link_to(linker *l) { dxshader::link_to(l); }
    void flush(c_program *p) { dxshader::flush(p); }
    void defined();
    void flush();

  private:
    ID3D11Buffer *buffer;
  };
}
