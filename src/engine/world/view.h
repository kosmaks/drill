#pragma once

#include <list>
#include "engine/virtual/service.h"
#include "engine/virtual/drawable.h"
#include "engine/virtual/module_source.h"

namespace drill {
  class view : public service {
  public:
    view(module_source *msource) : active(true), 
                                   _msource(msource) {}
    bool active;

    void init();
    void update();

    void add_drawable(drawable &d);

  protected:
    module_source *_msource;

  private:
    std::list<drawable*> _objects;
  };
}
