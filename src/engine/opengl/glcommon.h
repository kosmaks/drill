#pragma once

typedef enum {
  GL_VS,
  GL_FS
} glshader_t;

namespace drill {
  bool glinit();
  uint32_t glcompile_shader(const std::string &source, glshader_t type);
}
