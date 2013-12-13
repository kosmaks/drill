cbuffer InputColor : register(b0) {
  float4 buffer;
};

float4 PShader(float4 position : SV_POSITION) : SV_TARGET {
  return buffer;
}
