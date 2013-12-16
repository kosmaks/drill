#pragma once

#include "engine/core.h"
#include "engine/world.h"
#include "engine/views.h"

#include "views/table.h"
#include "views/billet.h"
#include "views/bit.h"
#include "views/drill.h"
#include "views/hand.h"
#include "views/holder.h"

class workbench_scene : public drill::scene {
public:
  workbench_scene(drill::platform &p) : drill::scene(p) { }
  ~workbench_scene();
  void init();
  void update(const drill::timeinfo_t& time);

private:
  drill::field<drill::input> input;

  drill::camera camera;
  table_view table;
  billet_view billet;
  bit_view bit;
  hand_view hand;
  drill_view drill;
  holder_view holder;

  drill::vector3_t position, rotation;
  float speed_limit, speed, acceleration, 
        coord, min_coord, max_coord;
  bool moving;

  drill::ehandler h_keydown, h_keyup;
  void keydown();
  void keyup();
};
