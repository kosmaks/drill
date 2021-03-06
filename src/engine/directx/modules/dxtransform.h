#pragma once

#include "engine/virtual/modules/transform.h"
#include "../dxheaders.h"
#include "dxshader.h"

namespace drill {
  class dxtransform : public dxshader, public transform {
  public:
    void link_to(linker *l) { dxshader::link_to(l); }
    void flush(c_program *p) { dxshader::flush(p); }
    void defined();
    void flush();

    transform& model_identity();
    transform& model_translate(const vector3_t &v);
    transform& model_rotate   (const vector4_t &v);
    transform& model_scale    (const vector3_t &v);

    transform& view_identity();
    transform& view_install(const vector3_t &position, 
                            const vector3_t &target, 
                            const vector3_t &up);
    transform& view_translate(const vector3_t &v);
    transform& view_rotate   (const vector4_t &v);
    transform& view_scale    (const vector3_t &v);

    transform& projection_identity();
    transform& projection_install(coord_t near, coord_t far, float aspect, float fov);

  private:
    typedef struct {
      D3DXMATRIX m_model,
                 m_projection,
                 m_view;
    } state_t;
    state_t state;
    ID3D11Buffer *buffer;
  };
}
