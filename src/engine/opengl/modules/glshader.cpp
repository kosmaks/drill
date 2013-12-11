#include <GL/glew.h>
#include "glshader.h"

using namespace drill;

char log[4096];

void glshader::link_to(linker *l) {
  gllinker *gll = (gllinker*)l;
  prog_id = gll->c_shader_program();
  glAttachShader(prog_id, shader_id);
}

void glshader::compile(const std::string &source, glshader::type_t type) {
  const char *src = source.c_str();
  int actual_length;
  LOG_DEBUG("Compiling OpenGL shader");

  shader_id = glCreateShader((type == GLSHADER_VERTEX) ? GL_VERTEX_SHADER : 
                                                         GL_FRAGMENT_SHADER);
  glShaderSource(shader_id, 1, &src, NULL);
  glCompileShader(shader_id);
  glGetShaderInfoLog(shader_id, 4095, &actual_length, log);

  if (actual_length > 0) {
    LOG_ERROR("Error compiling " << 
              ((type == GLSHADER_VERTEX) ? "vertex" : "fragment") <<
              " shader: " << log);
  }
}

void glshader::pass_param(const std::string &name, float value) {
  glUniform1f(glGetUniformLocation(prog_id, name.c_str()), value);
}

void glshader::pass_param(const std::string &name, const vector4_t &value) {
  glUniform4fv(glGetUniformLocation(prog_id, name.c_str()), 1, (const float*)&value);
}

void glshader::pass_param(const std::string &name, const vector3_t &value) {
  glUniform3fv(glGetUniformLocation(prog_id, name.c_str()), 1, (const float*)&value);
}

void glshader::pass_param(const std::string &name, const vector2_t &value) {
  glUniform2fv(glGetUniformLocation(prog_id, name.c_str()), 1, (const float*)&value);
}
