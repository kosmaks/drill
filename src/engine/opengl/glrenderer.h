#pragma once

#include "engine/virtual/renderer.h"

namespace drill {
  class glrenderer : public drill::renderer {
  public:
    glrenderer();
    virtual ~glrenderer();
  };
}
