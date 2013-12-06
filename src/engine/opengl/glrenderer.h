#pragma once

#include "engine/virtual/renderer.h"

namespace drill {
  class glrenderer : public renderer {
  public:
    glrenderer();
    virtual ~glrenderer();
  };
}
