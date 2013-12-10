#include "object.h"

using namespace drill;

object::object(module_source *msource) : _msource(msource) {
  compiler = msource->m_object_compiler;
}

void object::compile() {
  renderer = compiler->compile(&triangles);
}

void object::draw() {
  if (renderer) renderer->render();
}
