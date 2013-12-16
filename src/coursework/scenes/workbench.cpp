#include "workbench.h"

workbench_scene::~workbench_scene() {
  input().on_keydown.off(&h_keydown);
  input().on_keyup.off(&h_keyup);
}

void workbench_scene::init() {
  drill::scene::init();
  input = require<drill::input>();

  // Assign objects
  camera.set_scene(*this);
  table.set_scene(*this);
  billet.set_scene(*this);
  bit.set_scene(*this);
  hand.set_scene(*this);
  drill.set_scene(*this);
  holder.set_scene(*this);

  // Prefill data
  moving = false;
  min_coord = 5.0;
  max_coord = 5.3;
  coord = max_coord;
  speed = 0;

  // Setup camera
  camera.look_at({ 0.7, 5.2, 4 },
                 { 0, 3.8, 0 },
                 { 0, 1,   0 });

  // Initial position
  drill.position = { 0, 2.9, 0 };
  holder.position = { 0, 5.3, 0.35 };
  hand.position = { 0.3, 5.3, 0.13 };
  bit.position = { 0, 4.85, 0.35 };
  hand.rotation = { 1, 0, 0, 0 };
  billet.position = { -billet.size.x * billet.size.w / 2, 3.8, billet.size.z * billet.size.w / 2 };
  position = { 0, 0, 0 };
  rotation = { 0, 0, 0 };

  // Bindings
  h_keydown = [this] { keydown(); };
  input().on_keydown.on(&h_keydown);
  h_keyup = [this] { keyup(); };
  input().on_keyup.on(&h_keyup);
}

void workbench_scene::keydown() {
  switch (input().get_key()) {
    case 'Q': moving = true; break;
  }
}

void workbench_scene::keyup() {
  switch (input().get_key()) {
    case 'Q': moving = false; break;
  }
}

void workbench_scene::update(const drill::timeinfo_t& time) {
  drill::scene::update(time);

  acceleration = (moving) ? -0.001 : 0.001;

  float new_speed = speed + acceleration;

  if (coord + new_speed > min_coord && coord + new_speed < max_coord)  {
    speed = new_speed;
  } else {
    if (coord > max_coord) coord = max_coord;
    else if (coord < min_coord) coord = min_coord;
    speed = 0;
  }

  coord += speed;
  holder.position.y = coord;

  // dependencies
  bit.position.y = coord + 4.85 - 5.3;
  hand.rotation.w = 360 * (coord - min_coord) / (max_coord - min_coord);
}
