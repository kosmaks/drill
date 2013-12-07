#include "engine/core/app.h"
#include "engine/core/events.h"
#include "engine/opengl/glrenderer.h"

int main() {
  LOG_INFO("Application started");

  drill::glrenderer renderer;
  drill::application app;

  app.add_service(renderer);
  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
