#include "engine/core/app.h"
#include "view.h"

using namespace drill;

void view::init() {
  LOG_DEBUG("Initializing view");
}

void view::update(const timeinfo_t& timeinfo) {
  for (auto o : _objects) {
    o->draw();
  }
}

void view::add_drawable(drawable &d) {
  _objects.push_back(&d);
}
