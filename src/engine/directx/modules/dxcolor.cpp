#include "engine/core/config.h"
#include "dxcolor.h"

using namespace drill;

void dxcolor::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
}

void dxcolor::init() {
  compile(CFG_DX_COLOR_PS_PATH, DXSHADER_PIXEL);
}
