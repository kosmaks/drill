#include <cmath>
#include "engine/core.h"
#include "engine/world.h"
#include "engine/views.h"
#include "engine/resources.h"

#ifdef OPENGL
#include "engine/opengl.h"
#endif

#ifdef DIRECTX
#include "engine/directx.h"
#endif

class my_view : public drill::view {
public:
  void init() {
    compiler = require<drill::compiler>();
    linker = require<drill::linker>();
    transform = require<drill::transform>();
    material = require<drill::material>();

    reader.load_from_file("dist/ppsh.obj");
    LOG_INFO("loading from object");
    box = reader.to_object();
    c_box = compiler().compile(box);

    png_reader.load_from_file("dist/ppsh.png");
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
                         .model_scale({ 0.1, 0.1, 0.1 })
                         .model_translate({ 0.0, 0.0, -(angle) })
                         .model_rotate({ 0.0, 1.0, 0.0, 10 * (angle += 0.05) }))
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

int main() {
  LOG_INFO("Application started");

  drill::application app;

#ifdef DIRECTX
  drill::platform dxplatform;
  drill::dxcontext dxcontext("Course work: DirectX");
  drill::dxrenderer dxrenderer;
  drill::dxcompiler dxcompiler;
  drill::dxlinker dxlinker;
  drill::dxtransform dxtransform;
  drill::dxcolor dxcolor;
  drill::dxmaterial dxmaterial;

  dxplatform.define<drill::context>(dxcontext);
  dxplatform.define<drill::renderer>(dxrenderer);
  dxplatform.define<drill::compiler>(dxcompiler);
  dxplatform.define<drill::linker>(dxlinker);
  dxplatform.define<drill::transform>(dxtransform);
  dxplatform.define<drill::color>(dxcolor);
  dxplatform.define<drill::material>(dxmaterial);

  app.add_service(dxrenderer);

  dxtransform.init();
  dxcolor.init();
  dxmaterial.init();

  drill::scene dxscene(dxplatform);
  dxrenderer.use_scene(dxscene);

  drill::camera dxcamera;
  my_view dxmy;

  dxcamera.set_scene(dxscene);
  dxmy.set_scene(dxscene);
#endif

#ifdef OPENGL
  drill::platform glplatform;
  drill::glcontext glcontext("Course work: OpenGL");
  drill::glrenderer glrenderer;
  drill::glcompiler glcompiler;
  drill::gllinker gllinker;
  drill::gltransform gltransform;
  drill::glcolor glcolor;
  drill::glmaterial glmaterial;

  glplatform.define<drill::context>(glcontext);
  glplatform.define<drill::renderer>(glrenderer);
  glplatform.define<drill::compiler>(glcompiler);
  glplatform.define<drill::linker>(gllinker);
  glplatform.define<drill::transform>(gltransform);
  glplatform.define<drill::color>(glcolor);
  glplatform.define<drill::material>(glmaterial);

  app.add_service(glrenderer);

  gltransform.init();
  glcolor.init();
  glmaterial.init();

  drill::scene glscene(glplatform);
  glrenderer.use_scene(glscene);

  drill::camera glcamera;
  my_view glmy;

  glcamera.set_scene(glscene);
  glmy.set_scene(glscene);
#endif

  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
