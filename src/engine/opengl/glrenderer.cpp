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
  LOG_INFO("OpenGL version: " << glGetString(GL_VERSION));
  LOG_INFO("GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void glrenderer::update() {
  renderer::update();
  current_context->swap_buffers();
}
