#include "engine/core/app.h"
#include "renderer.h"

using namespace drill;

scene empty_scene((module_source*)nullptr);

renderer::renderer() {
  current_scene = &empty_scene;
}

renderer::~renderer() {
}

void renderer::defined() {
  current_context = &REQUIRE(context);
  current_context->load();
}

void renderer::use_scene(scene &new_scene) {
  current_scene = &new_scene;
  current_scene->init();
}

void renderer::update() {
  current_scene->update();
}
