#include <cmath>
#include "simple.h"

simple_scene::~simple_scene() {
  input().on_keydown.off(&h_keydown);
  input().on_keyup.off(&h_keyup);
  input().on_mousedown.off(&h_mousedown);
  input().on_mouseup.off(&h_mouseup);
}

void simple_scene::init() {
  drill::scene::init();
  input = require<drill::input>();

  camera.set_scene(*this);
  fire.set_scene(*this);

  camera.look_at({0, 3, 3},
                 {0, 0, 0},
                 {0, 1, 0});

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

void simple_scene::keydown() {
}

void simple_scene::keyup() {
}

void simple_scene::mousedown() {
}

void simple_scene::mouseup() {
}

void simple_scene::update(const drill::timeinfo_t& time) {
  drill::scene::update(time);
}
