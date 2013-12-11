#include "glmodule_source.h"
#include "modules/globject_compiler.h"
#include "modules/glcamera_controller.h"

using namespace drill;

void glmodule_source::init() {
  m_object_compiler = new globject_compiler();
  m_camera_controller = new glcamera_controller();
}

glmodule_source::~glmodule_source() {
  delete m_object_compiler;
  delete m_camera_controller;
}
