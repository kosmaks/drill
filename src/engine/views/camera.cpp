#include "camera.h"

using namespace drill;

void camera::init() {
  _context = require<context>();
  _transform = require<transform>();

  _offset = { 0, 0, 0 };
  _rotation_x = { -1, 0, 0, 0 };
  _rotation_y = { 0, -1, 0, 0 };
  _rotation_z = { 0, 0, -1, 0 };

  _aspect = _context().get_width() / _context().get_height();
  set_fov(60.0);
  set_near_cp(0.1);
  set_far_cp(100.0);
  look_at({ 0, 6, 7 },
          { 0, 0, 0 },
          { 0, 1, 0 });
}

void camera::update(const drill::timeinfo_t &time) {
  _transform().view_identity()
              .projection_identity()
              .view_install(_position, _target, _up)
              .projection_install(_near, _far, _aspect, _fov)
              .view_rotate(_rotation_x)
              .view_rotate(_rotation_y)
              .view_rotate(_rotation_z)
              .view_translate(_offset);
}

void camera::look_at(vector3_t pos, 
                     vector3_t target, 
                     vector3_t up) {
  _position = pos;
  _target = target;
  _up = up;
}

void camera::set_rotation_x(float angle) { _rotation_x.w = angle; }
void camera::set_rotation_y(float angle) { _rotation_y.w = angle; }
void camera::set_rotation_z(float angle) { _rotation_z.w = angle; }

void camera::set_position(const vector3_t& p) {
  _offset = { -p.x, -p.y, -p.z };
}
