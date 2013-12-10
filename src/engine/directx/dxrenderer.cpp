#include "engine/core/app.h"
#include "dxrenderer.h"

using namespace drill;

dxrenderer::dxrenderer(context &cont) : renderer(cont) {
}

dxrenderer::~dxrenderer() {
}

void dxrenderer::init() {
  renderer::init();
}

void dxrenderer::update() {
  renderer::update();
  current_context->swap_buffers();
}
