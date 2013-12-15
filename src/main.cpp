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

  if (argc >= 2 && std::string(argv[1]) == "opengl") {
    drill::glplatform *gl = new drill::glplatform();
    platform = gl;
  } else {
    drill::dxplatform *dx = new drill::dxplatform();
    platform = dx;
  }

  drill::renderer &renderer = platform().require<drill::renderer>();
  drill::input &input = platform().require<drill::input>();

  app.add_service(renderer);
  
  drill::scene scene(platform());
  renderer.use_scene(scene);

  drill::camera camera;
  my_view my;

  camera.set_scene(scene);
  my.set_scene(scene);

  drill::vector3_t camtarget = { 0, 0, 0 };
  camera.look_at({ 0, 3, 3 }, 
                 camtarget, 
                 { 0, 1, 0 });

  drill::ehandler kdh([&] {
      LOG_INFO("Key pressed: " << input.get_key());

      switch (input.get_key()) {
        case INPUT_KEY_UP: camtarget.y += 0.5; break;
        case INPUT_KEY_DOWN: camtarget.y -= 0.5; break;
        case INPUT_KEY_LEFT: camtarget.x -= 0.5; break;
        case INPUT_KEY_RIGHT: camtarget.x += 0.5; break;
      }

      camera.look_at({ 0, 3, 3 }, 
                     camtarget, 
                     { 0, 1, 0 });

    });
  input.on_keydown.on(&kdh);
  
  app.run();

  LOG_INFO("Cleaning up");
  delete &platform();

  LOG_INFO("Application terminated");
  return 0;
}
