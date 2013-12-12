#include "engine/core/config.h"
#include "dxtransform.h"

using namespace drill;

void dxtransform::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
}

void dxtransform::init() {
  compile(CFG_DX_TRANSFORM_VS_PATH, DXSHADER_VERTEX);
}
