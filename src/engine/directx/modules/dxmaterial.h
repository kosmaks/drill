#pragma once

#include "engine/virtual/modules/material.h"
#include "dxshader.h"

namespace drill {
  class dxmaterial : public dxshader, public material {
  public:
    void init();
    void link_to(linker *l) { _link_to(l); }
    void defined();
    void ready();
    material& use_texture(const texture &texture);
    material& color(const vector4_t &color);

  private:
    vector4_t _color;

    ID3D11Texture2D *_texture;
    ID3D11ShaderResourceView *texture_srv;
    ID3D11Buffer *buffer;
  };
}
