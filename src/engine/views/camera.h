#pragma once

#include "engine/core.h"
#include "engine/world.h"

namespace drill {
  class camera : public view {
  public:
    void init();
    void update(const drill::timeinfo_t &time);

    // field of view
    inline void  set_near_cp(float x) { _near = x; } 
    inline float get_near_cp()        { return _fov; } 
    inline void  set_far_cp(float x)  { _far = x; } 
    inline float get_far_cp()         { return _far; } 
    inline void  set_fov(float x)     { _fov = x; } 
    inline float get_fov()            { return _fov; } 
    inline float get_aspect()         { return _aspect; }

    inline const vector3_t& get_target() { return _target; }

    // position
    void look_at(vector3_t pos, 
                 vector3_t target, 
                 vector3_t up);

  private:
    field<context> _context;
    field<transform> _transform;

    float _aspect, _fov, _near, _far;
    vector3_t _position, _target, _up;
  };
}
