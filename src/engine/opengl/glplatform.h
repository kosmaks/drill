#pragma once

#include "engine/core/platform.h"
#include "engine/virtual/service.h"
#include "engine/opengl.h"

namespace drill {
  class glplatform : public platform {
  public:
    glplatform() : platform() {
      define<context>(_glcontext);
      define<renderer>(_glrenderer);
      define<compiler>(_glcompiler);
      define<linker>(_gllinker);
      define<transform>(_gltransform);
      define<color>(_glcolor);
      define<material>(_glmaterial);
      define<input>(_glinput);
    }

  private:
    glcontext  _glcontext;
    glrenderer _glrenderer;
    glcompiler _glcompiler;
    gllinker _gllinker;
    gltransform _gltransform;
    glcolor _glcolor;
    glmaterial _glmaterial;
    glinput _glinput;
  };
}
