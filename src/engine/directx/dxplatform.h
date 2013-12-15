#pragma once

#include "engine/core/platform.h"
#include "engine/virtual/service.h"
#include "engine/directx.h"

namespace drill {
  class dxplatform : public platform {
  public:
    dxplatform() : platform() {
      define<context>(_dxcontext);
      define<renderer>(_dxrenderer);
      define<compiler>(_dxcompiler);
      define<linker>(_dxlinker);
      define<transform>(_dxtransform);
      define<color>(_dxcolor);
      define<material>(_dxmaterial);
      define<input>(_dxinput);
      define<dilate>(_dxdilate);
    }

  private:
    dxcontext _dxcontext;
    dxrenderer _dxrenderer;
    dxcompiler _dxcompiler;
    dxlinker _dxlinker;
    dxtransform _dxtransform;
    dxcolor _dxcolor;
    dxmaterial _dxmaterial;
    dxinput _dxinput;
    dxdilate _dxdilate;
  };
}
