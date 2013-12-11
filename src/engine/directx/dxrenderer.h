#pragma once

#include "engine/virtual/renderer.h"
#include "engine/virtual/service.h"

namespace drill {
  class dxrenderer : public renderer {
  public:
    dxrenderer();
    virtual ~dxrenderer();

    void init();
    void update(const timeinfo_t &timeinfo);
  };
}
