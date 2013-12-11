#include "engine/core/config.h"
#include "engine/resources/file_system.h"
#include "gltransform.h"

using namespace drill;

void gltransform::init() {
  compile(file_system::read_text_file(CFG_GL_TRANSFORM_VS_PATH), GLSHADER_VERTEX);
}

