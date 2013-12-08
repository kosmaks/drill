#pragma once

#include "engine/world/object.h" 

namespace drill {
  class primitive : public object { public: virtual ~primitive(); };
  class object_square : public primitive { public: object_square(); };
}
