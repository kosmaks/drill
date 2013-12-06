#include "engine/core/app.h"
#include "engine/core/events.h"
#include "engine/opengl/glrenderer.h"

int main() {
  LOG_INFO("Application started");

  drill::application::config_t config;
  config._renderer = new drill::renderer;
  config._compiler = new drill::compiler;

  drill::application app(config);

  LOG_DEBUG("Clean up...");
  delete config._renderer;
  delete config._compiler;

  LOG_INFO("Application terminated");
  return 0;
}
