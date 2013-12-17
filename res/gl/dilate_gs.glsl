#version 410

layout (points) in;
layout (triangle_strip, max_vertices=4) out;
/*layout (points, max_vertices=1) out;*/

in vec3 _vertex[];
in vec3 _normal[];
in vec2 _texcoord[];
in mat4 PVM[];
in mat4 NM[];

out vec3 vertex;
out vec3 normal;
out vec2 texcoord;

void emit(vec4 pos) {
  normal = _normal[0] * abs(pos.y); 
  texcoord = _texcoord[0]; 
  vertex = _vertex[0]; 
  gl_Position = pos;
  EmitVertex();
}

void main(void) {
  float d = 0.04;
  vec4 p1, p2, p3, p4, inp;
  inp = gl_in[0].gl_Position;

  p1 = inp + vec4(-d,  d, 0, 0) / inp.w;
  p2 = inp + vec4(d,  -d, 0, 0) / inp.w;
  p3 = inp + vec4(-d, -d, 0, 0) / inp.w;
  p4 = inp + vec4(d,   d, 0, 0) / inp.w;

  emit(p3);
  emit(p1);
  emit(p2);
  emit(p4);
  EndPrimitive();
}
