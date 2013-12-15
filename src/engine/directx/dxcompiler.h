#pragma once

#include <map>
#include "engine/virtual/compiler.h"
#include "dxheaders.h"
#include "dxcontext.h"

namespace drill {
  class dxc_object : public c_object {
  public:
    void render();
    void free();
    uint32_t triangles_count, points_count;
    ID3D11Buffer *triangles, *points;
    dxhandle_t *handle;

  private:
    void draw(ID3D11Buffer *buffer, uint32_t count, D3D10_PRIMITIVE_TOPOLOGY type);
  };

  class dxcompiler : public compiler {
  public: 
    ~dxcompiler();
    void defined();
    c_object* compile(object &obj);

  private:
    std::map<void*, dxc_object*> _pool;
    dxhandle_t *handle;

    void gen_buffer(ID3D11Buffer **output, vertex_t *input, uint32_t count);
  };
}
