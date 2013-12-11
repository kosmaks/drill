#pragma once

#include "engine/virtual/module_source.h"
#include "engine/virtual/service.h"

namespace drill {
  class glmodule_source : public module_source, public service {
  public:
    ~glmodule_source();
    void init();
  };
}
