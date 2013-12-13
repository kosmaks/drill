#pragma once

#include "engine/core/field.h"
#include "engine/core/types.h"

namespace drill {
  class texture {
  public:
    typedef enum {
      TEXTURE_GS = 1,
      TEXTURE_RGB = 3,
      TEXTURE_RGBA = 4
    } format_t;

    texture();
    texture(format_t format, uint32_t width, uint32_t height, const uint8_t *data);
    ~texture();

    inline const uint8_t* get_data() const { return _data; }
    inline uint32_t get_width() const { return _width; }
    inline uint32_t get_height() const { return _height; }
    inline format_t get_format() const { return _format; }

    uint8_t* transfer_ownership();

  private:
    uint8_t *_data;
    uint32_t _width, _height;
    format_t _format;
    bool _transfered_ownership;
  };
}
