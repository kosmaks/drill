#include <GL/glew.h>
#include "engine/core/config.h"
#include "engine/resources/file_system.h"
#include "gltransform.h"
#include "../glcommon.h"
#include "../glmodule_source.h"

using namespace drill;

gltransform::gltransform(glmodule_source *source) : transform() {
  _source = source;
  auto code = file_system::read_text_file(CFG_GL_TRANSFORM_VS_PATH);
  vs = glcompile_shader(code, GL_VS);
  code = file_system::read_text_file(CFG_GL_SANDBOX_FS_PATH);
  fs = glcompile_shader(code, GL_FS);
}

void gltransform::link() {
  auto p = _source->current_shader_program();
  glAttachShader(p, vs);
  glAttachShader(p, fs);
}

void gltransform::ready() {
  auto time_loc = glGetUniformLocation(_source->current_shader_program(), "time");
  glUniform1f(time_loc, time);
}
