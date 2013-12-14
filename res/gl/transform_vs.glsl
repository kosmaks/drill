#version 120

uniform mat4 m_model;
uniform mat4 m_projection;
uniform mat4 m_view;

varying vec4 normal;
varying vec2 texcoord;

void main() {
  texcoord = gl_MultiTexCoord0.xy;
  normal = vec4(gl_Normal, 1.0);
  gl_Position = m_projection * m_view * m_model * gl_Vertex;
}
