#version 410

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 m_model;
uniform mat4 m_projection;
uniform mat4 m_view;

out vec4 normal;
out vec2 texcoord;
out vec4 _normal;
out vec2 _texcoord;

void main() {
  _texcoord = texcoord = vertex_texture;
  _normal = normal = vec4(vertex_normal, 1.0);
  mat4 PVM = m_projection * m_view * m_model;
  gl_Position = PVM * vec4(vertex_position, 1.0);
}
