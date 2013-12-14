#include "engine/core/config.h"
#include "engine/resources/file_system.h"
#include "glcolor.h"

using namespace drill;

void glcolor::defined() {
  compile(file_system::read_text_file(CFG_GL_COLOR_FS_PATH), GLSHADER_FRAGMENT);
}

void glcolor::ready() {
  pass_param("color", value);
}

