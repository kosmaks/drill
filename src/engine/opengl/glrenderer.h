#pragma once

#include "engine/virtual/renderer.h"
#include "engine/virtual/service.h"

namespace drill {
  class glrenderer : public renderer {
  public:
    glrenderer(context &cont);
    virtual ~glrenderer();

    void init();
    void update();
  };
}
