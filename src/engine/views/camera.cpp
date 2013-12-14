#include "camera.h"

using namespace drill;

void camera::init() {
  _context = require<context>();
  _transform = require<transform>();
}

void camera::update(const drill::timeinfo_t &time) {
  _transform().view_identity()
              .projection_identity()
              .view_rotate({ 1.0, 0.0, 0.0, 10 })
              .view_translate({ 0.0, -2.0, -1.0 })
              .projection_install(0.1, 100.0, 640.0 / 480.0, 60);
}
