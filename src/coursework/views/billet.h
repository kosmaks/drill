#pragma once

#include "engine/core.h"
#include "engine/world.h"
#include "engine/resources.h"

class billet_view : public drill::view {
public:
  billet_view();
  ~billet_view();
  void init();
  void update(const drill::timeinfo_t &time);

  std::string texture_path;

  drill::vector3_t position;
  drill::vector4_t rotation;
  drill::vector4_t size;

  drill::vertex_t& get_vertex(drill::uint32_t x, drill::uint32_t y, drill::uint32_t z);
  drill::vertex_t* get_vertices() { return object->get_points(); }
  void rebuild();
  void reassemble();

private:
  // dependencies
  drill::field<drill::compiler> compiler;
  drill::field<drill::linker> linker;
  drill::field<drill::transform> transform;
  drill::field<drill::material> material;
  drill::field<drill::dilate> dilate;

  // readers
  drill::png_reader png_reader;

  // drawable
  drill::object *object;
  drill::c_object *c_object;
  drill::c_program *c_program;
  drill::texture texture;
  drill::c_texture *c_texture;
};
