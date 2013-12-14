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
  float4x4 PV = mul(m_projection, m_view);
  float4x4 PVM = mul(PV, m_model);

  output.position = mul(PVM, position);
  output.normal = mul(PVM, normal);
  output.texcoord = texcoord;

  return output;
}
