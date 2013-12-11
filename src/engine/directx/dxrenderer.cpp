#include "engine/core/app.h"
#include "dxrenderer.h"

using namespace drill;

dxrenderer::~dxrenderer() {
}

void dxrenderer::init() {
  renderer::init();
}

void dxrenderer::update(const timeinfo_t &timeinfo) {
  current_context->clear_screen();
  renderer::update(timeinfo);
  current_context->swap_buffers();
}
