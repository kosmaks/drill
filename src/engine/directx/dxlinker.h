#pragma once

#include "engine/virtual/linker.h"

namespace drill {
  class dxlinker : public linker {
  public:
    linker& begin();
    linker& include(module &m);
    linker& end();
    linker& use();

    linker& update(module &m);

    void defined() {}
  };
}
