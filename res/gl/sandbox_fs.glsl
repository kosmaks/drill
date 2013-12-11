#version 120

uniform float time;

void main() {
  gl_FragColor = vec4(sin(time / 100), 0.5, 0.0, 1.0);
}
