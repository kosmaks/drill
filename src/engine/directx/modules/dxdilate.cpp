#include "engine/core/config.h"
#include "dxdilate.h"

using namespace drill;

void dxdilate::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
  compile(CFG_DX_DILATE_GS_PATH, "GSDilate", DXSHADER_GEOMERTY);
}
