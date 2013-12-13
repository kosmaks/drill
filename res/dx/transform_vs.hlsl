cbuffer InputMatrices : register(b0) {
  float4x4 m_model;
  float4x4 m_projection;
  float4x4 m_view;
};

struct VOut {
  float4 position : SV_POSITION;
};

VOut VShader(float4 position : POSITION) {
  VOut output;
  output.position = mul(position, m_model);
  return output;
}
