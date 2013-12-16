#pragma once

#include "engine/core.h"
#include "engine/world.h"
#include "engine/resources.h"

class bit_view : public drill::view {
public:
  bit_view();
  ~bit_view();
  void init();
  void update(const drill::timeinfo_t &time);

  std::string model_path,
              texture_path;

  drill::vector3_t position;
  drill::vector4_t rotation;

private:
  // dependencies
  drill::field<drill::compiler> compiler;
  drill::field<drill::linker> linker;
  drill::field<drill::transform> transform;
  drill::field<drill::material> material;

  // readers
  drill::wavefront_reader wf_reader;
  drill::png_reader png_reader;

  // drawable
  drill::object object;
  drill::texture texture;
  drill::c_object *c_object;
  drill::c_texture *c_texture;
  drill::c_program *c_program;
};
