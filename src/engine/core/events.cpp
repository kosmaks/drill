#include <algorithm>
#include "app.h"
#include "events.h"

using namespace drill;

void event::trigger() {
  for (auto callback: _callbacks) {
    (*callback)();
  }
  if (_once_callbacks.size() > 0) {
    for (auto callback: _once_callbacks) {
      (*callback)();
    }
    _once_callbacks.clear();
  }
}

void event::on(ehandler *callback) {
  _callbacks.push_back(callback);
}

void event::once(ehandler *callback) {
  _once_callbacks.push_back(callback);
}

void event::off(ehandler *callback) {
  auto f = [&callback] (ehandler *c) { return callback == c; };
  std::remove_if(_callbacks.begin(), _callbacks.end(), f);
  std::remove_if(_once_callbacks.begin(), _once_callbacks.end(), f);
}

void event::clear() {
  _callbacks.clear();
  _once_callbacks.clear();
}
