#include <GL/glew.h>
#include "gllinker.h"

using namespace drill;

linker& gllinker::begin() {
  shader_program = glCreateProgram();
  LOG_DEBUG("glCreateProgram() -> " << shader_program);
  return *this;
}

linker& gllinker::include(module &m) {
  m.link_to(this);
  return *this;
}

c_program* gllinker::create() {
  glLinkProgram(shader_program);
  LOG_DEBUG("glLinkProgram(" << shader_program << ")");
  glc_program* prog = new glc_program();
  prog->shader_program = shader_program;
  return prog;
}

void glc_program::use() {
  glUseProgram(shader_program);
  LOG_DEBUG("glUseProgram(" << shader_program << ")");
}
