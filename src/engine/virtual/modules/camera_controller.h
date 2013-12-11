#pragma once

#include "engine/core/types.h"
#include "engine/virtual/module.h"

namespace drill {
  class camera_controller : public module {
  public:
    virtual void set_pos(coord_t x, coord_t y, coord_t z) = 0;
    virtual void set_top(coord_t x, coord_t y, coord_t z) = 0;
    virtual void look_at(coord_t x, coord_t y, coord_t z) = 0;

    void set_pos(vector3_t &pos) { set_pos(pos.x, pos.y, pos.z); }
    void set_top(vector3_t &pos) { set_top(pos.x, pos.y, pos.z); }
    void look_at(vector3_t &pos) { look_at(pos.x, pos.y, pos.z); }
  };
}
