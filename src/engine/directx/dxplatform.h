#pragma once

#include "engine/core/platform.h"
#include "engine/virtual/service.h"
#include "engine/directx.h"

namespace drill {
  class dxplatform : public service, public platform {
  public:
    void init() {
      define<context>(_dxcontext);
      define<renderer>(_dxrenderer);
      define<compiler>(_dxcompiler);
      define<linker>(_dxlinker);
      define<transform>(_dxtransform);
      define<color>(_dxcolor);
      define<material>(_dxmaterial);

      _dxrenderer.init();
      _dxtransform.init();
      _dxcolor.init();
      _dxmaterial.init();
    }

    void update(const timeinfo_t &time) {
      _dxrenderer.update(time);
    }

  private:
    drill::dxcontext _dxcontext;
    drill::dxrenderer _dxrenderer;
    drill::dxcompiler _dxcompiler;
    drill::dxlinker _dxlinker;
    drill::dxtransform _dxtransform;
    drill::dxcolor _dxcolor;
    drill::dxmaterial _dxmaterial;
  };
}
