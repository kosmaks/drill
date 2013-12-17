#version 410

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texture;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 m_model;
uniform mat4 m_projection;
uniform mat4 m_view;

out vec3 vertex;
out vec3 normal;
out vec2 texcoord;
out vec3 _vertex;
out vec3 _normal;
out vec2 _texcoord;

out mat4 NM;
out mat4 VM;
out mat4 PVM;

void main() {
  VM = m_view * m_model;
  PVM = m_projection * m_view * m_model;
  NM = transpose(inverse(VM));

  vertex = (VM * vec4(vertex_position, 1.0)).xyz;
  _vertex = vertex;

  normal = normalize((NM * vec4(vertex_normal, 0.0)).xyz);
  _normal = normal;

  _texcoord = texcoord = vertex_texture;

  gl_Position = m_projection * vec4(vertex, 1.0);
}
