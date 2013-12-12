#include <memory.h>
#include "texture.h"

using namespace drill;

texture::texture(texture::format_t format, 
                 drill::uint32_t width, 
                 drill::uint32_t height, 
                 const drill::uint8_t *data) {
  if (data != nullptr) {
    size_t length = format * width * height;
    _format = format;
    _width = width;
    _height = height;
    _data = new uint8_t[length];
    memcpy(_data, data, length);
  } else {
    _data = nullptr;
    _width = 0;
    _height = 0;
  }
}

texture::texture() {
  _data = nullptr;
  _width = 0;
  _height = 0;
}

texture::~texture() {
  if (_data) {
    delete[] _data;
  }
}
