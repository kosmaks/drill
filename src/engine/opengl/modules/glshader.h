#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"
#include "../gllinker.h"

namespace drill {
  class glshader : public module {
  public:
    typedef enum {
      GLSHADER_VERTEX,
      GLSHADER_FRAGMENT
    } type_t;
    virtual ~glshader() {}

    virtual void link_to(linker *l);

  protected:
    uint32_t shader_id, prog_id; 

    void compile(const std::string &source, type_t type);
    void pass_param(const std::string &name, float value);
    void pass_param(const std::string &name, const vector2_t &value);
    void pass_param(const std::string &name, const vector3_t &value);
    void pass_param(const std::string &name, const vector4_t &value);
  };
}
