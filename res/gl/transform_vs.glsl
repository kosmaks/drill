#version 120

uniform mat4 m_model;
uniform mat4 m_projection;
uniform mat4 m_view;

varying vec4 normal;

void main() {
  vec4 pos = m_model * gl_Vertex;
  normal = pos;
  gl_Position = pos;
}
