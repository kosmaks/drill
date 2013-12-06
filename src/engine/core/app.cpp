#include "app.h"

using namespace drill;

application::application(const config_t &config) {
  _config = config;

  dependency(_config._renderer, "renderer");
  dependency(_config._compiler, "compiler");
}

application::~application() {
}

template<class T> void application::dependency(T *item, const std::string &title) {
  if (item == NULL) {
    LOG_ERROR("Unable to load module '" << title << "'!");
    throw "Module loading failure.";
  }
}
