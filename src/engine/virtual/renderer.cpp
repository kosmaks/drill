#include "engine/core/app.h"
#include "renderer.h"

using namespace drill;

renderer::renderer(context &cont) {
  current_context = &cont;
  current_scene = &empty_scene;
}

renderer::~renderer() {
}

void renderer::init() {
  LOG_DEBUG("Loading context");
  current_context->load();
}

void renderer::use_scene(scene &new_scene) {
  current_scene = &new_scene;
  current_scene->init();
}

void renderer::update() {
  current_scene->update();
}
