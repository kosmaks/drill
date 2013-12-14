#version 120

uniform vec4 color;
uniform sampler2D basic_texture;

varying vec2 texcoord;
varying vec4 normal;

void main() {
  /*float intensity = dot(vec3(0.0, 1.5, 0.0), normal.xyz);*/
  float intensity = 1;
  vec4 res = texture2D(basic_texture, texcoord.st);
  gl_FragColor = color * res * intensity;
}
