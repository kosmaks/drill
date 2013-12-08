#include "engine/core/app.h"
#include "engine/core/types.h"
#include "engine/core/events.h"
#include "engine/world/object.h"
#include "engine/opengl/glrenderer.h"
#include "engine/opengl/glcontext.h"

int main() {
  LOG_INFO("Application started");

  drill::glcontext cont("Course work: Drill");
  drill::glrenderer renderer(cont);
  drill::application app;

  drill::scene logo_scene;
  renderer.use_scene(logo_scene);

  app.add_service(renderer);
  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
