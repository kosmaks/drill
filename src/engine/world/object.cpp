#include "object.h"

using namespace drill;

object::object(module_source *msource) : _msource(msource) {
  _msource = msource;
  _compiler = msource->m_object_compiler;
  _transform = msource->m_transform;
}

void object::compile() {
  _renderer = _compiler->compile(&triangles);
}

void object::draw() {
  _msource->listen();
  _transform->time++;
  _transform->link();
  _msource->run();
  _transform->ready();

  if (_renderer) _renderer->render();
}
