#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "engine/world/object.h"
#include "engine/virtual/bridge.h"
#include "dxcontext.h"

namespace drill {
  class dxbridge_object : public bridge<object> {
  public:
    ~dxbridge_object();
    dxbridge_object(dxcontext &cont, object &target) : bridge(target), current_context(&cont) {} 
    void compile();
    void draw();

  private:
    dxcontext* current_context;
    vector4_t* colored_vertices;

    ID3D11Buffer *p_vbuffer;
  };
}
