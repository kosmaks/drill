#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include "engine/core/config.h"
#include "engine/resources/file_system.h"
#include "gltransform.h"

using namespace drill;

void gltransform::init() {
  compile(file_system::read_text_file(CFG_GL_TRANSFORM_VS_PATH), GLSHADER_VERTEX);
  model_identity();
  projection_identity();
  view_identity();
}

transform& gltransform::model_identity() {
  m_model = glm::mat4(1.0f);
  return *this;
}

transform& gltransform::projection_identity() {
  m_projection = glm::mat4(1.0f);
  return *this;
}

transform& gltransform::view_identity() {
  m_view = glm::mat4(1.0f);
  return *this;
}

transform& gltransform::model_translate(const vector3_t& v) {
  m_model *= glm::translate(v.x, v.y, v.z);
  return *this;
}

transform& gltransform::model_rotate(const vector4_t &v) {
  m_model *= glm::rotate(v.w, v.x, v.y, v.z);
  return *this;
}

transform& gltransform::model_scale(const vector3_t &v) {
  m_model *= glm::scale(v.x, v.y, v.z);
  return *this;
}

transform& gltransform::view_translate(const vector3_t &v) {
  m_view *= glm::translate(v.x, v.y, v.z);
  return *this;
}

transform& gltransform::view_rotate(const vector4_t &v) {
  m_view *= glm::rotate(v.w, v.x, v.y, v.z);
  return *this;
}

transform& gltransform::view_scale(const vector3_t &v) {
  m_view *= glm::scale(v.x, v.y, v.z);
  return *this;
}

transform& gltransform::projection_install(coord_t n, coord_t f, float aspect, float fov) {
  m_projection = glm::perspective(fov, aspect, n, f);
  return *this;
}

void gltransform::ready() {
  pass_param("m_model", m_model);
  pass_param("m_projection", m_projection);
  pass_param("m_view", m_view);
}
