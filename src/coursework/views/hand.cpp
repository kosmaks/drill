#include "hand.h"

hand_view::hand_view() : drill::view() {
  model_path = "dist/models/hand.obj";
  texture_path = "dist/textures/drill.png";

  position = { 0, 0, 0 };
  rotation = { 0, 0, 0, 0 };
  c_program = nullptr;
}

hand_view::~hand_view() {
  if (c_program != nullptr) delete c_program;
}

void hand_view::init() {
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

void hand_view::update(const drill::timeinfo_t &time) {

  c_program->use();

  transform().model_identity()
             .model_translate(position)
             .model_rotate(rotation)
             .model_rotate({ 0, 1, 0, 180 })
             .model_scale({ 0.7, 0.7, 0.7 })
             .flush(c_program);

  material().use_texture(c_texture)
            .color({ 1, 1, 1, 1 })
            .flush(c_program);

  c_object->render();
}

