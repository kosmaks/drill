#pragma once

#include "engine/virtual/modules/transform.h"
#include "../dxheaders.h"
#include "dxshader.h"

namespace drill {
  class dxtransform : public dxshader, public transform {
  public:
    void init();
    void link_to(linker *l) { _link_to(l); }
    void defined();
    void ready();

    transform& model_identity();
    transform& projection_identity();
    transform& view_identity();

    transform& model_translate      (const vector3_t &v);
    transform& model_rotate         (const vector4_t &v);
    transform& model_scale          (const vector3_t &v);
    transform& projection_translate (const vector3_t &v);
    transform& projection_rotate    (const vector4_t &v);
    transform& projection_scale     (const vector3_t &v);
    transform& view_translate       (const vector3_t &v);
    transform& view_rotate          (const vector4_t &v);
    transform& view_scale           (const vector3_t &v);

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
