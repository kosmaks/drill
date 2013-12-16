#include "bit.h"

bit_view::bit_view() : drill::view() {
  model_path = "dist/models/bit.obj";
  texture_path = "dist/textures/metal.png";

  position = { 0, 0, 0 };
  scale = { 1, 1, 1 };
  rotation = { 0, 0, 0, 0 };
  c_program = nullptr;
}

bit_view::~bit_view() {
  if (c_program != nullptr) delete c_program;
}

void bit_view::init() {
  // Load dependencies
  compiler = require<drill::compiler>();
  linker = require<drill::linker>();
  transform = require<drill::transform>();
  material = require<drill::material>();

  // Load model
  wf_reader.load_from_file(model_path);
  object = wf_reader.to_object();
  c_object = compiler().compile(object);

  // Load texture
  png_reader.load_from_file(texture_path);
  texture = png_reader.to_texture();
  c_texture = material().compile_texture(texture);

  // Init shaders
  c_program = linker().begin()
                      .include(transform())
                      .include(material())
                      .create();
}

void bit_view::update(const drill::timeinfo_t &time) {

  c_program->use();

  transform().model_identity()
             .model_translate(position)
             .model_rotate(rotation)
             .model_scale(scale)
             .model_scale({ 0.1, 0.15, 0.1 })
             .flush(c_program);

  material().use_texture(c_texture)
            .color({ 1, 1, 1, 1 })
            .flush(c_program);

  c_object->render();
}

