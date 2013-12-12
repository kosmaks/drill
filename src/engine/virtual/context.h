#pragma once

#include <string>
#include <typeinfo>
#include "engine/core/types.h"
#include "engine/core/events.h"
#include "engine/core/platform.h"

namespace drill {
  class context : public dependency {
  public:
    virtual ~context() {}
    virtual void load() = 0;
    virtual void swap_buffers() = 0;
    virtual void clear_screen() = 0;

    template<class T> T* get_info() { return (T*)info(typeid(T).hash_code()); }
    virtual void* info(size_t hash) = 0;

    event resize;
  };
}
