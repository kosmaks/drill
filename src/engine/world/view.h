#pragma once

#include <list>
#include "engine/virtual/service.h"

namespace drill {
  class view : public service {
  public:
    bool active = true;

  private:
    std::list<void*> _objects;
  };
}
