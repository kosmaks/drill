#version 120

uniform mat4 m_model;
uniform mat4 m_projection;
uniform mat4 m_view;

varying vec3 normal;
varying vec2 texcoord;

void main() {
  mat4 PVM = m_projection * m_view * m_model;
  vec4 pos = PVM * gl_Vertex;
  normal = (PVM * vec4(gl_Normal, 1.0)).xyz;
  texcoord = gl_MultiTexCoord0.xy;
  gl_Position = pos;
}
