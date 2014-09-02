#pragma once

#include "engine/core.h"
#include "engine/world.h"
#include "engine/views.h"

#include "fire.h"

class simple_scene : public drill::scene {
public:
  simple_scene(drill::platform &p) : drill::scene(p) { }
  ~simple_scene();
  void init();
  void update(const drill::timeinfo_t& time);

private:
  drill::field<drill::input> input;
  drill::ehandler h_keydown, h_keyup,
                  h_mousedown, h_mouseup;

  fire_view fire;

  drill::camera camera;

  drill::vector3_t position, rotation, 
                   cam_source, cam_target;

  bool moving, started, pause;

  void keydown();
  void keyup();
  void mousedown();
  void mouseup();
};
