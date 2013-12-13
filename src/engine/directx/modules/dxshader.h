#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"
#include "../dxlinker.h"
#include "../dxcontext.h"

namespace drill {
  class dxshader {
  public:
    typedef enum {
      DXSHADER_VERTEX,
      DXSHADER_PIXEL
    } type_t;
    virtual ~dxshader() {}

  protected:
    dxhandle_t *handle;
    ID3D10Blob *blob, *error;
    ID3D11VertexShader *pVS;
    ID3D11PixelShader *pPS;
    ID3D11InputLayout *layout;
    type_t type;

    virtual void _link_to(linker *l);
    void compile(const std::string &path, const std::string &entry, type_t type);
  };
}

