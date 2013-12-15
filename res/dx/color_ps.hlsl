cbuffer InputColor : register(b0) {
  float4 buffer;
};

float4 PSColor(float4 position : SV_POSITION, 
               float4 texcoord : TEXCOORD, 
               float4 normal : NORMAL) : SV_TARGET {
  float intensity = dot(float3(0.0, 2, 2.0), normal.xyz);
  return float4(texcoord.x, texcoord.y, 1, 1);
}
