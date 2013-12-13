cbuffer InputMatrices : register(b0) {
  float4x4 m_model;
  float4x4 m_projection;
  float4x4 m_view;
};

struct VOut {
  float4 position : SV_POSITION;
  float4 texcoord : TEXCOORD;
  float4 normal : NORMAL;
};

VOut VSTransform(float4 position : POSITION, 
                 float4 texcoord : TEXCOORD, 
                 float4 normal : NORMAL) {
  VOut output;
  float4x4 PVM = mul(m_view, m_projection);
  PVM = mul(m_model, PVM);
  output.position = mul(position, PVM);
  output.texcoord = texcoord;
  output.normal = mul(normal, PVM);
  output.position.w = 1.0;
  return output;
}
