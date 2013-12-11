#pragma once

#include "engine/virtual/modules/camera_controller.h"

namespace drill {
  class glcamera_controller : public camera_controller {
  public:
    glcamera_controller();
    void set_pos(coord_t x, coord_t y, coord_t z) {}
    void set_top(coord_t x, coord_t y, coord_t z) {}
    void look_at(coord_t x, coord_t y, coord_t z) {}
    void link();
  };
}
