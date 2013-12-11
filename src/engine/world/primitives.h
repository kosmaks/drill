#pragma once

#include "engine/world/object.h" 

namespace drill {
  class primitive : public object { 
    public: 
      primitive() : object() {}
      virtual ~primitive(); 
  };
  class object_square : public primitive { 
    public: object_square(); 
  };
}
