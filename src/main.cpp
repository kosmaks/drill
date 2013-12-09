#include "engine/core/app.h"
#include "engine/core/types.h"
#include "engine/core/events.h"
#include "engine/world/object.h"
#include "engine/world/primitives.h"
#include "engine/opengl/glrenderer.h"
#include "engine/opengl/glbridge_object.h"
#include "engine/opengl/glcontext.h"
#include "engine/resources/wavefront_reader.h"

int main() {
  LOG_INFO("Application started");

  drill::wavefront_reader reader;
  drill::object box;

  reader.load_from_file("dist/box.obj");
  reader.to_object(box);

  drill::glcontext cont("Course work: Drill");
  drill::glrenderer renderer(cont);
  drill::application app;
  app.add_service(renderer);

  drill::scene logo_scene;
  drill::view test;

  drill::glbridge_object bridge_object(box);
  bridge_object.compile();
  box.drawer = &bridge_object;

  logo_scene.add_view(test);
  test.add_drawable(box);

  renderer.use_scene(logo_scene);

  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
