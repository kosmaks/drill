#include <GL/glew.h>
#include "glmodule_source.h"
#include "modules/globject_compiler.h"
#include "modules/glcamera_controller.h"
#include "modules/gltransform.h"

using namespace drill;

void glmodule_source::init() {
  m_object_compiler = new globject_compiler();
  m_camera_controller = new glcamera_controller();
  m_transform = new gltransform(this);
}

glmodule_source::~glmodule_source() {
  delete m_object_compiler;
  delete m_camera_controller;
  delete m_transform;
}

void glmodule_source::listen() {
  shader_program = glCreateProgram();
}

void glmodule_source::run() {
  glLinkProgram(shader_program);
  glUseProgram(shader_program);
}
