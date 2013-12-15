#include "dxlinker.h"

using namespace drill;

void dxlinker::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
}

linker& dxlinker::begin() {
  return *this;
}

linker& dxlinker::include(module &m) {
  m.link_to(this);
  return *this;
}

c_program* dxlinker::create() {
  dxc_program *prog = new dxc_program();
  prog->handle = handle;
  return prog;
}

void dxc_program::use() {
  handle->devcon->VSSetShader(NULL, 0, 0);
  handle->devcon->GSSetShader(NULL, 0, 0);
  handle->devcon->PSSetShader(NULL, 0, 0);
}
