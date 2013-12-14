#pragma once

#include "engine/virtual/module.h"

namespace drill {
  class transform : public module {
  public:


    virtual transform& model_identity() = 0;
    virtual transform& model_translate(const vector3_t &v) = 0;
    virtual transform& model_rotate   (const vector4_t &v) = 0;
    virtual transform& model_scale    (const vector3_t &v) = 0;

    virtual transform& view_identity() = 0;
    virtual transform& view_install(const vector3_t &position, 
                                    const vector3_t &target, 
                                    const vector3_t &up) = 0;

    virtual transform& projection_identity() = 0;
    virtual transform& projection_install(coord_t near, coord_t far, float aspect, float fov) = 0;
  };
}
