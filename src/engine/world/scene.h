#pragma once

#include <list>
#include "engine/virtual/service.h"
#include "view.h"

namespace drill {
  class scene : public service {
  public:
    scene();
    virtual ~scene();

    void add_view(view& v);

    // service
    void update(const timeinfo_t &timeinfo);

  private:
    std::list<view*> _views;
  };
}
