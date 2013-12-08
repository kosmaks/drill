#pragma once

#include <list>
#include "engine/virtual/service.h"
#include "engine/virtual/drawable.h"

namespace drill {
  class view : public service {
  public:
    bool active = true;

    void init();
    void update();

    void add_drawable(drawable &d);

  private:
    std::list<drawable*> _objects;
  };
}