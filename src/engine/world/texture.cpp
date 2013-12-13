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
  _transfered_ownership = false;
}

texture::texture() {
  _data = nullptr;
  _width = 0;
  _height = 0;
  _transfered_ownership = false;
}

uint8_t *texture::transfer_ownership() {
  _transfered_ownership = true;
  return _data;
}

texture::~texture() {
  if (_data != nullptr && !_transfered_ownership) {
    delete[] _data;
  }
}
