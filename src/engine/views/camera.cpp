#include "camera.h"

using namespace drill;

void camera::init() {
  _context = require<context>();
  _transform = require<transform>();

  _aspect = _context().get_width() / _context().get_height();
  set_fov(60.0);
  set_near_cp(0.1);
  set_far_cp(100.0);
}

void camera::update(const drill::timeinfo_t &time) {
  _transform().view_identity()
              .projection_identity()
              .view_rotate({ 1.0, 0.0, 0.0, 10 })
              .view_translate({ 0.0, -2.0, -1.0 })
              .projection_install(_near, _far, _aspect, _fov);
}