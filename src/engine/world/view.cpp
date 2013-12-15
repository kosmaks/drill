#include "view.h"

using namespace drill;

void view::set_scene(scene &s) {
  c_scene = &s;
  c_scene->add_service(this);
  init();
}
