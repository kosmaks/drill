#include "app.h"
#include "engine/virtual/context.h"

using namespace drill;

application::application() : _running(false), _frozen(false) {
}

application::~application() {
}

void application::add_service(service& serv) {
  _services.push_back(&serv);
  serv.init();
}

void application::run() {
  if (_frozen) {
    _frozen = false;
    return;
  }

  _running = true;
  while (_running) {
    if (_frozen) { continue; }
    for (auto serv : _services) {
      serv->update();
    }
  }
}

void application::freeze() {
  _frozen = true;
}

void application::kill() {
  _running = false;
}
