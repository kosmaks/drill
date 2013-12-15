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
    drill::glcontext  _glcontext;
    drill::glrenderer _glrenderer;
    drill::glcompiler _glcompiler;
    drill::gllinker _gllinker;
    drill::gltransform _gltransform;
    drill::glcolor _glcolor;
    drill::glmaterial _glmaterial;
    drill::glinput _glinput;
  };
}
