#pragma once

#include "engine/core.h"
#include "engine/world.h"
#include "engine/views.h"

#include "views/table.h"
#include "views/billet.h"

class workbench_scene : public drill::scene {
public:
  workbench_scene(drill::platform &p) : drill::scene(p) { }
  ~workbench_scene();
  void init();

private:
  drill::field<drill::input> input;

  drill::camera camera;
  table_view table;
  billet_view billet;

  drill::vector3_t target, source;
  drill::ehandler h_keydown;
  void keydown();
};
