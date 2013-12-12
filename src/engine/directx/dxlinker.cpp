#include "dxlinker.h"

using namespace drill;

linker& dxlinker::begin() {
  return *this;
}

linker& dxlinker::include(module &m) {
  m.link_to(this);
  return *this;
}

linker& dxlinker::end() {
  return *this;
}

linker& dxlinker::use() {
  return *this;
}

linker& dxlinker::operator<<(module &m) {
  m.ready();
  return *this;
}
