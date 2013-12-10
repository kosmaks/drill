#pragma once

#include "engine/world/object.h" 
#include "engine/virtual/module_source.h" 

namespace drill {
  class primitive : public object { 
    public: 
      primitive(module_source *msource) : object(msource) {}
      virtual ~primitive(); 
  };
  class object_square : public primitive { 
    public: object_square(module_source *msource); 
  };
}
