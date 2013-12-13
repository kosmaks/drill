#version 120

uniform vec4 color;

varying vec4 normal;

void main() {
  float intensity = 1;
  /*float intensity = dot(vec3(0, 0, 10), normalize(normal.xyz));*/
  /*intensity = (intensity > 1.0) ? 1.0 :*/
              /*(intensity > 0.5) ? 0.5 :*/
                                  /*0.2;*/
  gl_FragColor = intensity * color;
}
