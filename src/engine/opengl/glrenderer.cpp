#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glcommon.h"
#include "glrenderer.h"

using namespace drill;

glrenderer::glrenderer(context &cont) : renderer(cont) {
  glinit();
}

glrenderer::~glrenderer() {
}

void glrenderer::init() {
  renderer::init();
  LOG_DEBUG("Initializing GLEW");
  glewExperimental = GL_TRUE;
  glewInit();
}

void glrenderer::update() {
  renderer::update();
  current_context->swap_buffers();
}
