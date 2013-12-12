#include "scene.h"

using namespace drill;

scene::scene(platform &p) : c_platform(p) {
}

scene::~scene() {
}

void scene::add_service(service* s) {
  _services.push_back(s);
  s->init();
}

void scene::update(const timeinfo_t &timeinfo) {
  for (auto s : _services) {
    s->update(timeinfo);
  }
}
