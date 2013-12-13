#include <GL/glew.h>
#include "engine/core/config.h"
#include "engine/resources/file_system.h"
#include "glmaterial.h"

using namespace drill;

void glmaterial::init() {
  compile(file_system::read_text_file(CFG_GL_MATERIAL_FS_PATH), GLSHADER_FRAGMENT);
  color({ 1.0, 1.0, 1.0, 1.0 });
}

material& glmaterial::use_texture(const texture &texture) {
  glGenTextures(1, &tex_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  glTexImage2D(GL_TEXTURE_2D,
               0,                     // minmap level
               GL_RGBA,               // internal format
               texture.get_width(),
               texture.get_height(),
               0,                     // border
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               texture.get_data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  return *this;
}

material& glmaterial::color(const vector4_t &color) {
  _color = color;
  return *this;
}

void glmaterial::ready() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  pass_param("primary_texture", (uint32_t)0);
  pass_param("color", _color);
}
