#include "workbench.h"

workbench_scene::~workbench_scene() {
  input().on_keydown.off(&h_keydown);
}

void workbench_scene::init() {
  drill::scene::init();
  input = require<drill::input>();

  camera.set_scene(*this);
  table.set_scene(*this);
  billet.set_scene(*this);

  billet.position = { -billet.size.x * billet.size.w / 2, 1.7, billet.size.z * billet.size.w / 2 };

  position = { 0, 0, 0 };
  rotation = { 0, 0, 0 };

  h_keydown = [this] { keydown(); };
  input().on_keydown.on(&h_keydown);
}

void workbench_scene::keydown() {
  switch (input().get_key()) {
    case INPUT_KEY_UP: rotation.x += 1; break;
    case INPUT_KEY_DOWN: rotation.x -= 1; break;
    case INPUT_KEY_LEFT: rotation.y += 1; break;
    case INPUT_KEY_RIGHT: rotation.y -= 1; break;
    case 'W': position.z -= 0.1; break;
    case 'S': position.z += 0.1; break;
    case 'A': position.x -= 0.1; break;
    case 'D': position.x += 0.1; break;
    case 'R': position.y += 0.1; break;
    case 'F': position.y -= 0.1; break;
    case 'T': billet.position.y += 0.01; break;
    case 'G': billet.position.y -= 0.01; break;
  }

  camera.set_position(position);
  camera.set_rotation_x(rotation.x);
  camera.set_rotation_y(rotation.y);
}
