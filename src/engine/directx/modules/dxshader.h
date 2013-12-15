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
      DXSHADER_GEOMERTY,
      DXSHADER_PIXEL
    } type_t;
    virtual ~dxshader() {}

    void link_to(linker *l);
    void flush(c_program *p);
    virtual void flush() = 0;

  protected:
    dxhandle_t *handle;
    ID3D10Blob *blob, *error;
    ID3D11VertexShader *pVS;
    ID3D11GeometryShader *pGS;
    ID3D11PixelShader *pPS;
    ID3D11InputLayout *layout;
    type_t type;

    void compile(const std::string &path, const std::string &entry, type_t type);
  };
}

