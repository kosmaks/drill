#include <lodepng.h>
#include "engine/core/app.h"
#include "png_reader.h"

using namespace drill;

void png_reader::load_from_file(const std::string &path) {
  LOG_DEBUG("Loading texture '" << path << "'");
  if (lodepng::decode(_buffer, width, height, path.c_str())) {
    LOG_ERROR("Unable to load png image '" << path << "'");
  }
}

texture png_reader::to_texture() {
  vector2_t size = { width, height };
  return texture(texture::TEXTURE_RGBA, width, height, &_buffer[0]);
}
