struct INPUT {
  float4 position : SV_POSITION;
  float2 texcoord : TEXCOORD;
  float4 normal : NORMAL;
  float3 light0 : LIGHT0;
};

[maxvertexcount(6)]
void GSDilate(point INPUT i[1], inout TriangleStream<INPUT> stream) {
  INPUT p1, p2, p3, p4;
  p1 = p2 = p3 = p4 = i[0];
  float d = 0.02;

  p1.position.x -= d;
  p1.position.y += d;
  p1.position.z += d;
  
  p2.position.x += d;
  p2.position.y += d;
  p2.position.z += d;
  
  p3.position.x -= d;
  p3.position.y -= d;
  p3.position.z += d;
  
  p4.position.x += d;
  p4.position.y -= d;
  p4.position.z += d;

  stream.Append(p1);
  stream.Append(p3);
  stream.Append(p2);

  stream.Append(p2);
  stream.Append(p3);
  stream.Append(p4);
}

