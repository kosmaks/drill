#pragma once

#include <map>
#include <type_traits>
#include <typeinfo>
#include <exception>
#include "types.h"

#define PLATFORM_DEF_T template<class T> \
  typename std::enable_if<std::is_base_of<dependency, T>::value, T&>::type

#define INCLUDE(x) (current_platform->include<x>())
#define REQUIRE(x) (current_platform->require<x>())

namespace drill {
  struct unresolved_dependency_exception : std::exception {
  public:
    unresolved_dependency_exception(const char *name) : _name(name) {}
    const char *what() const noexcept { return _name; }
  private:
    const char *_name;
  };

  class platform;

  class dependency { 
  public: 
    platform *current_platform; 
    virtual void defined() = 0;
  };

  class platform {
  public:
    PLATFORM_DEF_T define(T &obj) {
      auto dep = ((dependency*)&obj);
      dep->current_platform = this;
      _maps[typeid(T).hash_code()] = &obj;
      dep->defined();
      return obj;
    }

    PLATFORM_DEF_T require() {
      T &t = include<T>();
      if (&t == nullptr) {
        throw unresolved_dependency_exception(typeid(T).name());
      }
      return t;
    }

    PLATFORM_DEF_T include() {
      return *((T*)_maps[typeid(T).hash_code()]);
    }

  private:
    std::map<uint32_t, void*> _maps; 
  };
}
