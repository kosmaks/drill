#pragma once

#include "engine/virtual/modules/material.h"
#include "dxshader.h"

namespace drill {
  class dxc_texture : public c_texture {
  public:
    dxc_texture() {}
    dxc_texture(ID3D11DeviceContext *d, ID3D11ShaderResourceView *t);
    void use();

  private:
    ID3D11DeviceContext *devcon;
    ID3D11ShaderResourceView *texture_srv; 
  };

  class dxmaterial : public dxshader, public material {
  public:
    ~dxmaterial();
    void link_to(linker *l) { dxshader::link_to(l); }
    void flush(c_program *p) { dxshader::flush(p); }
    void defined();
    void flush();
    c_texture* compile_texture(texture &texture);
    material& use_texture(c_texture *c_texture);
    material& color(const vector4_t &color);

  private:
    vector4_t _color;
    std::map<void*, dxc_texture*> _pool;

    ID3D11Texture2D *_texture;
    ID3D11ShaderResourceView *texture_srv;
    ID3D11Buffer *buffer;
  };
}
