#include "engine/core/config.h"
#include "engine/resources/file_system.h"
#include "../glcommon.h"
#include "glcamera_controller.h"

using namespace drill;

glcamera_controller::glcamera_controller() {
  auto source = file_system::read_text_file(CFG_GL_CAMERA_VS_PATH);
  auto vs = glcompile_shader(source, GL_VS);
}

void glcamera_controller::link() {
}
