#include "app.h"
#include "events.h"

using namespace drill;

void event::trigger(void *param) {
  for (auto callback: _callbacks) {
    callback(param);
  }
  if (_once_callbacks.size() > 0) {
    for (auto callback: _once_callbacks) {
      callback(param);
    }
    _once_callbacks.clear();
  }
}

void event::on(const callback_t &callback) {
  _callbacks.push_back(callback);
}

void event::once(const callback_t &callback) {
  _once_callbacks.push_back(callback);
}

void event::off(const callback_t &callback) {
  _callbacks.remove(callback);
}

void event::clear() {
  _callbacks.clear();
  _once_callbacks.clear();
}
