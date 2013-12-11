#include "engine/core/app.h"
#include "engine/core/platform.h"
#include "engine/opengl/glrenderer.h"
#include "engine/opengl/glcontext.h"
#include "engine/opengl/glcompiler.h"
#include "engine/opengl/gllinker.h"
#include "engine/opengl/modules/gltransform.h"
#include "engine/opengl/modules/glcolor.h"
#include "engine/world/scene.h"
#include "engine/world/view.h"
#include "engine/world/primitives.h"
#include "engine/virtual/compiler.h"
#include "engine/virtual/modules/transform.h"
#include "engine/virtual/modules/color.h"
#include "engine/resources/wavefront_reader.h"

class my_view : public drill::view {
public:
  my_view(drill::platform &p) : 
    drill::view(p),
    compiler  (p.require<drill::compiler>()),
    linker    (p.require<drill::linker>()),
    transform (p.require<drill::transform>()),
    color     (p.require<drill::color>())
  {

    // load box from file
    reader.load_from_file("dist/box.obj");
    reader.to_object(box);

    // compile everything
    c_box = compiler.compile(box);

    linker.begin()
          .include(transform)
          .include(color)
          .end();
  }

  void update(const drill::timeinfo_t &time) {
    linker << color.set(0.0, 0.5, 1.0);
    linker.use();
    c_box->render();
  }

private:
  drill::compiler &compiler;
  drill::linker &linker;
  drill::transform &transform;
  drill::color &color;

  drill::wavefront_reader reader;
  drill::object box;
  drill::c_object *c_box;
};

int main() {
  LOG_INFO("Application started");

  // rendering
  drill::platform platform;
  drill::application app;
  drill::glcontext context("Course work: drill");
  drill::glrenderer renderer;
  drill::glcompiler compiler;
  drill::gllinker linker;
  // modules
  drill::gltransform transform;
  drill::glcolor color;

  platform.define<drill::context>(context);
  platform.define<drill::renderer>(renderer);
  platform.define<drill::compiler>(compiler);
  platform.define<drill::linker>(linker);
  platform.define<drill::transform>(transform);
  platform.define<drill::color>(color);

  app.add_service(renderer);

  transform.init();
  color.init();

  drill::scene scene;
  my_view my(platform);
  scene.add_view(my);

  renderer.use_scene(scene);

  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
