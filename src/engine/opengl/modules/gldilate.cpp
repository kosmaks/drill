#include "engine/resources/file_system.h"
#include "engine/core/config.h"
#include "gldilate.h"

using namespace drill;

void gldilate::link_to(linker *l) {
  glshader::link_to(l);
}

void gldilate::defined() {
  compile(file_system::read_text_file(CFG_GL_DILATE_GS_PATH), GLSHADER_GEOMETRY);
}
