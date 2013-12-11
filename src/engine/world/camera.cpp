#include "camera.h"

using namespace drill;

camera::camera(module_source *msource) {
  _controller = msource->m_camera_controller;
}

void camera::draw() {
}
