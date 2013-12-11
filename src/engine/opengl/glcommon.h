#pragma once

#include "engine/core/types.h"

typedef enum {
  GL_VS,
  GL_FS
} glshader_t;

namespace drill {
  bool glinit();
}
