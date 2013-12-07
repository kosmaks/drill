#include "engine/core/app.h"
#include "engine/core/events.h"
#include "engine/opengl/glrenderer.h"
#include "engine/opengl/glcontext.h"

int main() {
  LOG_INFO("Application started");

  drill::glcontext cont("Course work: Drill");
  drill::glrenderer renderer(cont);
  drill::application app;

  app.add_service(renderer);
  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
