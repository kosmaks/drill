#version 120

uniform vec4 color;
uniform sampler2D basic_texture;

varying vec2 texcoord;
varying vec3 normal;

void main() {
  float intensity = dot(vec3(2.0, 2.0, 0.0), normal);
  /*float intensity = 1;*/
  vec4 res = texture2D(basic_texture, texcoord.st);
  gl_FragColor = color * intensity * res;
}
