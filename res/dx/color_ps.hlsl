cbuffer InputColor : register(b0) {
  float4 buffer;
};

float4 PSColor(float4 position : SV_POSITION, 
               float4 texcoord : TEXCOORD, 
               float4 normal : NORMAL) : SV_TARGET {
  float intensity = dot(float3(2.0, 2.0, 0.0), normalize(normal.xyz));
  return buffer;
}
