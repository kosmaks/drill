#include "engine/core/app.h"
#include "engine/core/platform.h"
#include "engine/opengl/glrenderer.h"
#include "engine/opengl/glcontext.h"
#include "engine/opengl/glmodule_source.h"
#include "engine/world/scene.h"
#include "engine/world/view.h"
#include "engine/world/primitives.h"
#include "engine/virtual/modules/object_compiler.h"
#include "engine/resources/wavefront_reader.h"

int main() {
  LOG_INFO("Application started");

  drill::platform platform;
  drill::application app;
  drill::glcontext context("Course work: drill");
  drill::glrenderer renderer;
  drill::glmodule_source msource;
  drill::wavefront_reader reader;

  platform.define<drill::context>(context);
  platform.define<drill::renderer>(renderer);
  platform.define<drill::module_source>(msource);

  app.add_service(renderer);
  app.add_service(msource);

  drill::scene scene(&msource);
  drill::view main(&msource);
  drill::object box(&msource);

  reader.load_from_file("dist/box.obj");
  reader.to_object(box);

  box.compile();

  scene.add_view(main);
  main.add_drawable(box);
  renderer.use_scene(scene);

  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
