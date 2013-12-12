#pragma once

#include <string>
#include <vector>
#include "engine/world/texture.h"

namespace drill {
  class png_reader {
  public:
    void load_from_file(const std::string &path);
    texture to_texture();
  private:
    std::vector<uint8_t> _buffer;
    unsigned int width, height;
  };
}
