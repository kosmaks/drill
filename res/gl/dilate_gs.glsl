#version 410

layout (points) in;
layout (triangle_strip, max_vertices=3) out;

in vec4 _normal[];
in vec2 _texcoord[];

out vec4 normal;
out vec2 texcoord;

void emit(vec4 pos) {
  normal = _normal[0]; 
  texcoord = _texcoord[0]; 
  gl_Position = pos;
  EmitVertex();
}

void main(void) {
  float d = 0.04;
  vec4 p1, p2, p3, p4, inp;
  p1 = p2 = p3 = p4 = inp = gl_in[0].gl_Position;

  p1 += vec4(-d, d, 0, 0) / inp.w;
  p2 += vec4(d, -d, 0, 0) / inp.w;
  p3 += vec4(-d, -d, 0, 0) / inp.w;
  p4 += vec4(d, -d, 0, 0) / inp.w;

  emit(p1);
  emit(p3);
  emit(p2);

  emit(p2);
  emit(p3);
  emit(p4);

  EndPrimitive();
}
