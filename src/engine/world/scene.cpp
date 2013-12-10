#include "scene.h"

using namespace drill;

scene::scene(module_source *msource) {
  _msource = msource;
}

scene::~scene() {
}

void scene::add_view(view& v) {
  _views.push_back(&v);
  v.init();
}

void scene::update() {
  for (auto v : _views) {
    if (v->active) {
      v->update();
    }
  }
}
