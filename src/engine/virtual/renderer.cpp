#include "engine/core/app.h"
#include "renderer.h"

using namespace drill;

renderer::renderer(context &cont) {
  current_context = &cont;
}

renderer::~renderer() {
}

void renderer::init() {
  LOG_DEBUG("Loading context");
  current_context->load();
}
