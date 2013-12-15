#pragma once

#include <map>
#include "engine/core/types.h"
#include "engine/core/platform.h"
#include "engine/world/object.h"

namespace drill {
  class c_object { 
    public: 
      virtual ~c_object() {}
      virtual void render() = 0; 
      virtual void free() = 0;
  }; 

  class compiler : public dependency {
  public:
    virtual ~compiler() {}
    virtual c_object* compile(object &obj) = 0;
  };
}
