#pragma once

#include <GLM/glm.hpp>
#include "engine/core/types.h"
#include "engine/virtual/module.h"
#include "../gllinker.h"

namespace drill {
  class glshader : public module {
  public:
    typedef enum {
      GLSHADER_VERTEX,
      GLSHADER_FRAGMENT,
      GLSHADER_GEOMETRY
    } type_t;
    virtual ~glshader() {}

    void defined() {}
    void link_to(linker *l);
    void flush(c_program *p);
    virtual void flush() = 0;

  protected:
    uint32_t shader_id, prog_id; 

    void compile(const std::string &source, type_t type);
    void pass_param(const std::string &name, float value);
    void pass_param(const std::string &name, uint32_t value);
    void pass_param(const std::string &name, const vector2_t &value);
    void pass_param(const std::string &name, const vector3_t &value);
    void pass_param(const std::string &name, const vector4_t &value);
    void pass_param(const std::string &name, const glm::mat4 &value);
  };
}
