#include <cmath>
#include "engine/core/app.h"
#include "engine/core/field.h"
#include "engine/core/platform.h"
#include "engine/world/scene.h"
#include "engine/world/view.h"
#include "engine/world/primitives.h"
#include "engine/virtual/compiler.h"
#include "engine/virtual/modules/transform.h"
#include "engine/virtual/modules/color.h"
#include "engine/virtual/modules/material.h"
#include "engine/resources/wavefront_reader.h"
#include "engine/resources/png_reader.h"

#ifdef OPENGL
#include "engine/opengl/glrenderer.h"
#include "engine/opengl/glcontext.h"
#include "engine/opengl/glcompiler.h"
#include "engine/opengl/gllinker.h"
#include "engine/opengl/modules/gltransform.h"
#include "engine/opengl/modules/glcolor.h"
#include "engine/opengl/modules/glmaterial.h"
#endif

#ifdef DIRECTX
#include "engine/directx/dxrenderer.h"
#include "engine/directx/dxcontext.h"
#include "engine/directx/dxcompiler.h"
#include "engine/directx/dxlinker.h"
#include "engine/directx/modules/dxtransform.h"
#include "engine/directx/modules/dxcolor.h"
#include "engine/directx/modules/dxmaterial.h"
#endif

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

    angle = 1;
  }

  void update(const drill::timeinfo_t &time) {
    linker()
      .update(transform().model_identity()
                         .projection_identity()
                         //.model_scale({ 0.035, 0.035, 0.035 })
                         .projection_rotate({ 1.0, 0.0, 0.0, -30 })
                         .model_rotate({ 0.0, 1.0, 0.0, angle }))
      .update(material().color({ 0.0, 0.5, 1.0, 1.0 }))
      .use();
    angle++;
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

  my_view dxmy;
  drill::scene dxscene(dxplatform);
  dxrenderer.use_scene(dxscene);
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

  my_view glmy;
  drill::scene glscene(glplatform);
  glrenderer.use_scene(glscene);
  glmy.set_scene(glscene);
#endif

  app.run();

  LOG_INFO("Application terminated");
  return 0;
}
