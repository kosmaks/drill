#include <cmath>
#include "engine/core.h"
#include "engine/world.h"
#include "engine/views.h"
#include "engine/resources.h"

class my_view : public drill::view {
public:
  void init() {
    compiler = require<drill::compiler>();
    linker = require<drill::linker>();
    transform = require<drill::transform>();
    material = require<drill::material>();

    reader.load_from_file("dist/wbox.obj");
    LOG_INFO("loading from object");
    box = reader.to_object();
    c_box = compiler().compile(box);

    png_reader.load_from_file("dist/texture.png");
    texture = png_reader.to_texture();
    material().use_texture(texture);

    linker()
      .begin()
      .include(transform())
      .include(material())
      .end();

    angle = 0.0;
  }

  void update(const drill::timeinfo_t &time) {
    linker()
      .update(transform().model_identity()
                         .model_rotate({ 0.0, 1.0, 0.0, (angle += 0.1) }))
      .update(material())
      .use();
    c_box->render();
  }

private:
  drill::field<drill::compiler> compiler;
  drill::field<drill::linker> linker;
  drill::field<drill::transform> transform;
  drill::field<drill::material> material;

  drill::wavefront_reader reader;
  drill::png_reader png_reader;
  drill::object box;
  drill::texture texture;
  drill::c_object *c_box;

  float angle;
};

int main(int argc, char **argv) {
  LOG_INFO("Application started");

  drill::application app;
  drill::field<drill::platform> platform;
  drill::field<drill::renderer> renderer;

  if (argc >= 2 && std::string(argv[1]) == "opengl") {
    drill::glplatform *gl = new drill::glplatform();
    app.add_service(*gl);
    platform = gl;
  } else {
    drill::dxplatform *dx = new drill::dxplatform();
    app.add_service(*dx);
    platform = dx;
  }

  renderer = platform().include<drill::renderer>();
  
  drill::scene scene(platform());
  renderer().use_scene(scene);

  drill::camera camera;
  my_view my;

  camera.set_scene(scene);
  my.set_scene(scene);

  camera.look_at({ 0, 3, 3 }, 
                 { 0, 0, 0 }, 
                 { 0, 1, 0 });

  app.run();

  LOG_INFO("Cleaning up");
  delete &platform();

  LOG_INFO("Application terminated");
  return 0;
}
