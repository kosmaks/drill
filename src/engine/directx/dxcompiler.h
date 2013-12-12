#pragma once

#include <map>
#include "engine/virtual/compiler.h"
#include "dxheaders.h"
#include "dxcontext.h"

namespace drill {
  class dxc_object : public c_object {
  public:
    void render();
    uint32_t count;
    ID3D11Buffer *buffer;
    dxhandle_t *handle;
  };

  class dxcompiler : public compiler {
  public: 
    ~dxcompiler();
    void defined();
    c_object* compile(object &obj);

  private:
    std::map<void*, dxc_object*> _pool;
    dxhandle_t *handle;
  };
}
