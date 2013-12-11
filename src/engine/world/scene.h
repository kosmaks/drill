#pragma once

#include <list>
#include "engine/virtual/service.h"
#include "engine/virtual/module_source.h"
#include "view.h"

namespace drill {
  class scene : public service {
  public:
    scene(module_source *msource);
    virtual ~scene();

    void add_view(view& v);

    // service
    void update(const timeinfo_t &timeinfo);

  private:
    std::list<view*> _views;
    module_source *_msource;
  };
}
