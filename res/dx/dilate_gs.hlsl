struct INPUT {
  float4 position : SV_POSITION;
  float2 texcoord : TEXCOORD;
  float4 normal : NORMAL;
};

[maxvertexcount(6)]
void GSDilate(point INPUT i[1], inout TriangleStream<INPUT> stream) {
  INPUT p1, p2, p3, p4;
  INPUT input = i[0];
  float d = 0.04;

  p1 = p2 = p3 = p4 = input;

  p1.position += float4(-d, d, 0, 0) / input.position.w;
  p2.position += float4(d, d, 0, 0) / input.position.w;
  p3.position += float4(-d, -d, 0, 0) / input.position.w;
  p4.position += float4(d, -d, 0, 0) / input.position.w;

  p1.texcoord += float2(-0.01, 0.01);
  p2.texcoord += float2(0.01, 0.01);
  p3.texcoord += float2(-0.01, -0.01);
  p4.texcoord += float2(0.01, -0.01);

  stream.Append(p1);
  stream.Append(p3);
  stream.Append(p2);

  stream.Append(p2);
  stream.Append(p3);
  stream.Append(p4);
}

