#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/core/app.h"
#include "glcommon.h"
#include "glrenderer.h"

using namespace drill;

glrenderer::glrenderer() : renderer() {
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

  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void glrenderer::update(const timeinfo_t &timeinfo) {
  current_context->clear_screen();
  renderer::update(timeinfo);
  current_context->swap_buffers();
}
