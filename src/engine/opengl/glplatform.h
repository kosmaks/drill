#pragma once

#include "engine/core/platform.h"
#include "engine/virtual/service.h"
#include "engine/opengl.h"

namespace drill {
  class glplatform : public service, public platform {
  public:
    void init() {
      LOG_ERROR("here");
      define<context>(_glcontext);
      define<renderer>(_glrenderer);
      define<compiler>(_glcompiler);
      define<linker>(_gllinker);
      define<transform>(_gltransform);
      define<color>(_glcolor);
      define<material>(_glmaterial);

      _glrenderer.init();
      _gltransform.init();
      _glcolor.init();
      _glmaterial.init();
    }

    void update(const timeinfo_t &time) {
      _glrenderer.update(time);
    }

  private:
    drill::glcontext  _glcontext;
    drill::glrenderer _glrenderer;
    drill::glcompiler _glcompiler;
    drill::gllinker _gllinker;
    drill::gltransform _gltransform;
    drill::glcolor _glcolor;
    drill::glmaterial _glmaterial;
  };
}
