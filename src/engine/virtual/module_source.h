#pragma once

#include <list>
#include "engine/core/platform.h"
#include "module.h"
#include "modules/object_compiler.h"

namespace drill {
  class module_source : public dependency {
  public:
    object_compiler *m_object_compiler;
  };
}
