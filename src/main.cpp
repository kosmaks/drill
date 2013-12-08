#include "engine/core/app.h"
#include "engine/core/types.h"
#include "engine/core/events.h"
#include "engine/world/object.h"
#include "engine/world/primitives.h"
#include "engine/opengl/glrenderer.h"
#include "engine/opengl/glbridge_object.h"
#include "engine/opengl/glcontext.h"

int main() {
  LOG_INFO("Application started");

  drill::glcontext cont("Course work: Drill");
  drill::glrenderer renderer(cont);
  drill::application app;
  app.add_service(renderer);

  drill::scene logo_scene;
  drill::view test;
  drill::object_square square;

  drill::glbridge_object bridge_object(square);
  bridge_object.compile();
  square.drawer = &bridge_object;

  logo_scene.add_view(test);
  test.add_drawable(square);

  renderer.use_scene(logo_scene);

  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
