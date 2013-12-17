#include <cmath>
#include "workbench.h"

workbench_scene::~workbench_scene() {
  input().on_keydown.off(&h_keydown);
  input().on_keyup.off(&h_keyup);
  input().on_mousedown.off(&h_mousedown);
  input().on_mouseup.off(&h_mouseup);
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
  skybox.set_scene(*this);

  // Prefill data
  started = moving = false;
  min_coord = 5.0;
  max_coord = 5.3;
  power_max = 100;
  coord = max_coord;
  speed = 0;
  power = 0;
  height = 0.715;
  size = 1;
  sx = sz = 0;
  pause = false;
  stop_k = 1;

  // Setup camera
  cam_source = { 0.7, 5.2, 3.7 };
  cam_target = { 0, 3.8, 0 };
  camera.look_at(cam_source,
                 cam_target,
                 { 0, 1,   0 });

  // Initial position
  drill.position = { 0, 2.9, 0 };
  holder.position = { 0, 5.3, 0.33 };
  hand.position = { 0.3, 5.3, 0.13 };
  bit.position = { 0, 4.85, 0.35 };
  skybox.position = { 0, 5.5, -5 };
  skybox.rotation = { 0, 1, 0, 30 };
  holder.rotation = { 0, 1, 0, 0 };
  bit.rotation = { 0, 1, 0, 0 };
  hand.rotation = { 1, 0, 0, 0 };
  billet.position = { -billet.size.x * billet.size.w / 2, 3.8, billet.size.z * billet.size.w / 2 };
  position = { 0, 0, 0 };
  rotation = { 0, 0, 0 };

  // Bindings
  h_keydown = [this] { keydown(); };
  h_keyup = [this] { keyup(); };
  h_mousedown = [this] { mousedown(); };
  h_mouseup = [this] { mouseup(); };
  input().on_keydown.on(&h_keydown);
  input().on_keyup.on(&h_keyup);
  input().on_mousedown.on(&h_mousedown);
  input().on_mouseup.on(&h_mouseup);
}

void workbench_scene::keydown() {
  if (pause) return;
  switch (input().get_key()) {
    case 'Q': moving = true; break;
    case 'S': started = !started; break;

    case INPUT_KEY_LEFT: sx = -0.002; break;
    case INPUT_KEY_RIGHT: sx = 0.002; break;
    case INPUT_KEY_UP: sz = -0.002; break;
    case INPUT_KEY_DOWN: sz = 0.002; break;
  }
}

void workbench_scene::keyup() {
  if (pause) return;

  switch (input().get_key()) {
    case 'Q': moving = false; break;

    case 'E': size += 0.1; break; 
    case 'D': size -= 0.1; break; 
    case 'R': 
      billet.size.y += 5; 
      billet.rebuild();
      break; 
    case 'F': 
      billet.size.y -= 5; 
      billet.rebuild();
      break; 
  }
  sx = sz = 0;
}

void workbench_scene::mousedown() {
  pause = !pause;
}

void workbench_scene::mouseup() {
}

void workbench_scene::update(const drill::timeinfo_t& time) {
  drill::scene::update(time);

  if (pause) return;

  //
  // Sizes
  bit.scale.x = bit.scale.z = size;

  //
  // Rotation

  float power_acc = (started) ? 1.0 : -1.0;
  float new_power = power + power_acc;
  power = (power + new_power >= power_max || 
           power + new_power <= 0) ?
          (started) ? power : 0
           : new_power;

  bit.rotation.w += power;
  holder.rotation.w += power;

  if (started) {

    //
    // Bit movement

    float acceleration = (moving) ? -0.001 : 0.001;
    float new_speed = speed + acceleration;

    if (coord + new_speed > min_coord && coord + new_speed < max_coord)  {
      speed = new_speed;
    } else {
      if (coord > max_coord) coord = max_coord;
      else if (coord < min_coord) coord = min_coord;
      speed = 0;
    }
  
    if (!moving) stop_k = 1;
    coord += speed * stop_k;
    holder.position.y = coord;

    // dependencies
    float k = (1 - (coord - min_coord) / (max_coord - min_coord));
    bit.position.y = coord + 4.85 - 5.3;
    hand.rotation.w = -180 * k;
    camera.look_at({ cam_source.x, cam_source.y + 0.5f * k, cam_source.z + (-1.5f) * k },
                   cam_target, { 0, 1, 0 });

    float tip = bit.position.y - height;
    if (tip <= billet.position.y + billet.size.y * billet.size.w) {
      stop_k = (handle_collision(tip)) ? 0.3 : 1;
      return;
    } else {
      stop_k = 1;
    }
  }

  billet.position.x += sx;
  billet.position.z += sz;
}

bool workbench_scene::handle_collision(float tip) {
  float r = size * 1.5;
  float x = (bit.position.x - billet.position.x) / billet.size.w;
  float z = (bit.position.z - billet.position.z) / billet.size.w;
  int changed = 0;
  drill::uint32_t depth = (tip - billet.position.y) / billet.size.w;

  drill::int32_t _x, _z;

  for (drill::int32_t i = -r; i <= r; i++)
  for (drill::int32_t j = -r; j <= r; j++) {
    _x = i + x;
    _z = j + z;

    if (_x < 0 || _z < 0 || 
        _x >= billet.size.x || 
        _z >= billet.size.z ||
        (i*i + j*j) > (r*r)) continue;

    for (drill::uint32_t k = billet.size.y; k > depth; k--) {
      billet.get_vertex(_x, k, _z).vertex = { 0, 0, 0 };
    }
    changed++;
  }

  if (changed > 2) {
    billet.reassemble();
    return true;
  } else {
    return false;
  }
}
