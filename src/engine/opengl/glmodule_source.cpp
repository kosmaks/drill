#include "glmodule_source.h"
#include "modules/globject_compiler.h"

using namespace drill;

glmodule_source::glmodule_source() {
  m_object_compiler = new globject_compiler();
}

glmodule_source::~glmodule_source() {
  delete m_object_compiler;
}
