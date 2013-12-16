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
#include "views/skybox.h"

class workbench_scene : public drill::scene {
public:
  workbench_scene(drill::platform &p) : drill::scene(p) { }
  ~workbench_scene();
  void init();
  void update(const drill::timeinfo_t& time);

private:
  drill::field<drill::input> input;
  drill::ehandler h_keydown, h_keyup;

  drill::camera camera;
  table_view table;
  billet_view billet;
  bit_view bit;
  hand_view hand;
  drill_view drill;
  holder_view holder;
  skybox_view skybox;

  drill::vector3_t position, rotation, 
                   cam_source, cam_target;

  float speed_limit, speed,
        coord, min_coord, max_coord,
        power, power_max, 
        height, size,
        sx, sz;
  bool moving, started;

  void handle_collision(float tip);
  void keydown();
  void keyup();
};
