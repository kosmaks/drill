#include "engine/core.h"
#include "billet.h"

billet_view::billet_view() : drill::view() {
  texture_path = "dist/textures/workbench1.png";

  position = { 0, 0, 0 };
  rotation = { 0, 0, 0, 0 };
  size = { 60, 20, 40, 0.01 };

  c_program = nullptr;
  c_object = nullptr;
  object = nullptr;
  angle = 0;
}

billet_view::~billet_view() {
  if (object != nullptr) delete object;
  if (c_program != nullptr) delete c_program;
}

void billet_view::init() {
  // Load dependencies
  compiler = require<drill::compiler>();
  linker = require<drill::linker>();
  transform = require<drill::transform>();
  material = require<drill::material>();
  dilate = require<drill::dilate>();

  // Load model
  if (object != nullptr) delete object;

  object = new drill::object(0, size.x * size.y * size.z);
  drill::vertex_t *points = object->get_points();

  drill::uint32_t i = 0;
  drill::vector3_t up = { 0, 1, 0 },
                   down = { 0, -1, 0 },
                   left = { -1, 0, 0 },
                   right = { 1, 0, 0 },
                   forward = { 0, 0, 1 },
                   back = { 0, 0, -1 };

  for (drill::uint32_t x = 0; x < size.x; ++x)
  for (drill::uint32_t y = 0; y < size.y; ++y)
  for (drill::uint32_t z = 0; z < size.z; ++z) {
    points[i].vertex = { x * size.w, y * size.w, z * size.w };
    points[i].texture = { ((float)x) / size.x, ((float)z) / size.z };
    points[i].normal = (x == 0) ? left :
                       (x == size.x - 1) ? right :
                       (y == 0) ? down :
                       (y == size.y - 1) ? up :
                       (z == 0) ? back :
                       (z == size.z - 1) ? forward :
                       back;
    i += 1;
  }

  // Load texture
  png_reader.load_from_file(texture_path);
  texture = png_reader.to_texture();
  c_texture = material().compile_texture(texture);

  // Compile
  c_object = compiler().compile(*object);

  // Init shaders
  c_program = linker().begin()
                      .include(transform())
                      .include(dilate())
                      .include(material())
                      .create();
}

void billet_view::update(const drill::timeinfo_t &time) {

  c_program->use();

  transform().model_identity()
             .model_rotate(rotation)
             .model_translate(position)
             .flush(c_program);

  material().use_texture(c_texture)
            .flush(c_program);

  dilate().flush(c_program);

  //angle += 1;
  //drill::uint32_t row = angle;

  //for (drill::uint32_t i = row * 100; 
       //(i < (row + 1) * 100) && (i < size.x * size.y * size.z);
       //++i) {
    //object->get_points(i)->vertex = { 0, 0, 0 };
  //}

  //c_object->free();
  //c_object = compiler().compile(*object);
  c_object->render();
}
