#include "workbench.h"

workbench_scene::~workbench_scene() {
}

void workbench_scene::init() {
  drill::scene::init();
  input = require<drill::input>();

  camera.set_scene(*this);
  table.set_scene(*this);
  billet.set_scene(*this);

  billet.position = { 0, 1.7, 0 };

  source = { 0, 3, 3 };
  target = camera.get_target(); 
  h_keydown = [this] { keydown(); };
  input().on_keydown.on(&h_keydown);
}

void workbench_scene::keydown() {
  switch (input().get_key()) {
    case INPUT_KEY_UP: target.y += 0.1; break;
    case INPUT_KEY_DOWN: target.y -= 0.1; break;
    case INPUT_KEY_LEFT: target.x -= 0.1; break;
    case INPUT_KEY_RIGHT: target.x += 0.1; break;
    case 'W': source.z -= 0.1; break;
    case 'S': source.z += 0.1; break;
    case 'A': source.x -= 0.1; break;
    case 'D': source.x += 0.1; break;
    case 'R': source.y += 0.1; break;
    case 'F': source.y -= 0.1; break;
    case 'T': billet.position.y += 0.01; break;
    case 'G': billet.position.y -= 0.01; break;
  }

  camera.look_at(source,
                 target,
                 { 0, 1, 0 });

  LOG_DEBUG("Y = " << target.y);
}
