#pragma once

#include "engine/core.h"
#include "engine/world.h"

namespace drill {
  class camera : public view {
  public:
    void init();
    void update(const drill::timeinfo_t &time);

  private:
    field<context> _context;
    field<transform> _transform;
  };
}
