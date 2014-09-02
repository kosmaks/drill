#include "engine/core.h"
#include "fire.h"

fire_view::fire_view() : drill::view() {
  position = { 0, 0, 0 };
  rotation = { 0, 0, 0, 0 };
  size = { 30, 10, 25, 0.015 };

  c_program = nullptr;
  c_object = nullptr;
  object = nullptr;
}

fire_view::~fire_view() {
  if (object != nullptr) delete object;
  if (c_program != nullptr) delete c_program;
}

void fire_view::init() {
  // Load dependencies
  compiler = require<drill::compiler>();
  linker = require<drill::linker>();
  transform = require<drill::transform>();
  color = require<drill::color>();
  dilate = require<drill::dilate>();
  fire = require<drill::fire>();

  // Load model
  rebuild();

  // Init shaders
  c_program = linker().begin()
                      .include(transform())
                      .include(fire())
                      .include(color())
                      .create();
}

void fire_view::update(const drill::timeinfo_t &time) {

  c_program->use();

  transform().model_identity()
             .model_rotate(rotation)
             .model_translate(position)
             .flush(c_program);

  dilate().flush(c_program);

  color().set({ 1, 0, 0, 1 }).flush(c_program);

  c_object->render();
}

drill::vertex_t& fire_view::get_vertex(drill::uint32_t x, drill::uint32_t y, drill::uint32_t z) {
  drill::uint32_t i = x * size.y * size.z + y * size.z + z;
  if (i >= size.x * size.y * size.z) i = 0;
  return object->get_points()[i];
}

void fire_view::rebuild() {
  if (object != nullptr) delete object;
  object = new drill::object(0, 1);
  drill::vertex_t *points = object->get_points();

  points->vertex = { 0, 0, 0 };
  points->texture = { 0, 0 };
  points->normal = { 0, 1, 0 };

  reassemble();
}

void fire_view::reassemble() {
  if (c_object != nullptr) c_object->free();
  c_object = compiler().compile(*object);
}

