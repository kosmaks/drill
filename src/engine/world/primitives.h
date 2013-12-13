#pragma once

#include "engine/world/object.h" 

namespace drill {
  class primitive : public object { 
    public: 
      primitive(uint32_t s) : object(s) {}
  };
  class object_square : public primitive { 
    public: object_square(); 
  };
}
