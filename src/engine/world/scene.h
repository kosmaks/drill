#pragma once

#include <list>
#include "engine/core/platform.h"
#include "engine/virtual/service.h"

namespace drill {
  class scene : public service {
  public:
    scene(platform &p);
    virtual ~scene();

    void add_service(service* s);

    // service
    void update(const timeinfo_t &timeinfo);

    platform &c_platform;

  private:
    std::list<service*> _services;
  };
}
