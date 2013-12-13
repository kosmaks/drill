#version 120

uniform vec4 color;

varying vec3 normal;

void main() {
  /*float intensity = 1;*/
  float intensity = dot(vec3(2, 2, 0), normal);
  /*intensity = (intensity > 1.0) ? 1.0 :*/
              /*(intensity > 0.5) ? 0.5 :*/
                                  /*0.2;*/
  gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}
