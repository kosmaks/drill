#version 120

uniform vec4 color;

varying vec3 normal;

void main() {
  gl_FragColor = color;
}
