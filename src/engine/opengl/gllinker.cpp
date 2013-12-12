#include <GL/glew.h>
#include "gllinker.h"

using namespace drill;

linker& gllinker::begin() {
  shader_program = glCreateProgram();
  return *this;
}

linker& gllinker::include(module &m) {
  m.link_to(this);
  return *this;
}

linker& gllinker::end() {
  glLinkProgram(shader_program);
  return *this;
}

uint32_t gllinker::c_shader_program() {
  return shader_program;
}

linker& gllinker::use() {
  glUseProgram(shader_program);
  return *this;
}

linker& gllinker::update(module &m) {
  m.ready();
  return *this;
}
