#version 410

uniform vec4 color;
uniform sampler2D basic_texture;

in vec2 texcoord;
in vec4 normal;
out vec4 frag_color;

void main() {
  /*float intensity = dot(vec3(0.0, 1.5, 0.0), normal.xyz);*/
  float intensity = 1;
  vec4 res = texture(basic_texture, texcoord.st);
  vec4 color = color * res * intensity;
  frag_color = color;
}
