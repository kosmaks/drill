#pragma once

#include <list>
#include "engine/core/types.h"
#include "engine/virtual/module.h"

namespace drill {
  class compiled_object {
  public:
    virtual ~compiled_object() {}
    virtual void render() {};
  };

  class object_compiler : public module {
  public:
    virtual ~object_compiler() { for (compiled_object* o : _to_destroy) delete o; }
    virtual compiled_object* compile(coordset_t *triangles) = 0;

  private:
    std::list<compiled_object*> _to_destroy;
  };
}
