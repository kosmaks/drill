#include "camera.h"

using namespace drill;

void camera::init() {
  _context = require<context>();
  _transform = require<transform>();

  _aspect = _context().get_width() / _context().get_height();
  set_fov(60.0);
  set_near_cp(0.1);
  set_far_cp(100.0);
  look_at({ 0, 3, 3 },
          { 0, 0, 0 },
          { 0, 1, 0 });
}

void camera::update(const drill::timeinfo_t &time) {
  _transform().view_identity()
              .projection_identity()
              .view_install(_position, _target, _up)
              .projection_install(_near, _far, _aspect, _fov);
}

void camera::look_at(vector3_t pos, 
                     vector3_t target, 
                     vector3_t up) {
  _position = pos;
  _target = target;
  _up = up;
}
