#include "engine/core/app.h"
#include "engine/core/field.h"
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
#include "engine/resources/png_reader.h"

#ifdef DIRECTX
#include "engine/directx/dxrenderer.h"
#include "engine/directx/dxcontext.h"
#include "engine/directx/dxcompiler.h"
#include "engine/directx/dxlinker.h"
#include "engine/directx/modules/dxtransform.h"
#include "engine/directx/modules/dxcolor.h"
#endif

class my_view : public drill::view {
public:
  void init() {
    compiler = require<drill::compiler>();
    linker = require<drill::linker>();
    transform = require<drill::transform>();
    color = require<drill::color>();

    reader.load_from_file("dist/wbox.obj");
    reader.to_object(box);
    c_box = compiler().compile(box);

    png_reader.load_from_file("dist/texture.png");
    texture = png_reader.to_texture();

    linker()
      .begin()
      .include(transform())
      .include(color())
      .end();
  }

  void update(const drill::timeinfo_t &time) {
    linker()
      .update(transform().model_scale({ 0.995, 1.0, 1.0})
                         .model_rotate({ 1.0 , 0.0 , 0.0, 0.2 }))
      .update(color().red(1.0))
      .use();
    c_box->render();
  }

private:
  drill::field<drill::compiler> compiler;
  drill::field<drill::linker> linker;
  drill::field<drill::transform> transform;
  drill::field<drill::color> color;

  drill::wavefront_reader reader;
  drill::png_reader png_reader;
  drill::object box;
  drill::texture texture;
  drill::c_object *c_box;
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

  dxplatform.define<drill::context>(dxcontext);
  dxplatform.define<drill::renderer>(dxrenderer);
  dxplatform.define<drill::compiler>(dxcompiler);
  dxplatform.define<drill::linker>(dxlinker);
  dxplatform.define<drill::transform>(dxtransform);
  dxplatform.define<drill::color>(dxcolor);

  app.add_service(dxrenderer);

  dxtransform.init();
  dxcolor.init();

  my_view dxmy;
  drill::scene dxscene(dxplatform);
  dxrenderer.use_scene(dxscene);
  dxmy.set_scene(dxscene);

#endif

  drill::platform glplatform;
  drill::glcontext glcontext("Course work: OpenGL");
  drill::glrenderer glrenderer;
  drill::glcompiler glcompiler;
  drill::gllinker gllinker;
  drill::gltransform gltransform;
  drill::glcolor glcolor;

  glplatform.define<drill::context>(glcontext);
  glplatform.define<drill::renderer>(glrenderer);
  glplatform.define<drill::compiler>(glcompiler);
  glplatform.define<drill::linker>(gllinker);
  glplatform.define<drill::transform>(gltransform);
  glplatform.define<drill::color>(glcolor);

  app.add_service(glrenderer);

  gltransform.init();
  glcolor.init();

  my_view glmy;
  drill::scene glscene(glplatform);
  glrenderer.use_scene(glscene);
  glmy.set_scene(glscene);

  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
