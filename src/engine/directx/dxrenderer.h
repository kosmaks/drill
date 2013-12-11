#pragma once

#include "engine/virtual/renderer.h"
#include "engine/virtual/service.h"

namespace drill {
  class dxrenderer : public renderer {
  public:
    virtual ~dxrenderer();

    void init();
    void update(const timeinfo_t &timeinfo);
  };
}
