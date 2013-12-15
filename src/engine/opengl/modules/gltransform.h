#pragma once

#include <GLM/glm.hpp>
#include "engine/virtual/modules/transform.h"
#include "glshader.h"

namespace drill {
  class gltransform : public glshader, public transform {
  public:
    void link_to(linker *l) { glshader::link_to(l); }
    void flush(c_program *p) { glshader::flush(p); }
    void defined();
    void flush();

    transform& model_identity();
    transform& model_translate(const vector3_t &v);
    transform& model_rotate   (const vector4_t &v);
    transform& model_scale    (const vector3_t &v);

    transform& view_identity();
    transform& view_install(const vector3_t &position, 
                            const vector3_t &target, 
                            const vector3_t &up);
    transform& view_translate(const vector3_t &v);
    transform& view_rotate   (const vector4_t &v);
    transform& view_scale    (const vector3_t &v);

    transform& projection_identity();
    transform& projection_install(coord_t near, coord_t far, float aspect, float fov);

  private:
    glm::mat4 m_model,
              m_projection,
              m_view;
  };
}
