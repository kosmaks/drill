cbuffer InputMatrices : register(b0) {
  float4x4 m_model;
  float4x4 m_projection;
  float4x4 m_view;
};

struct VOut {
  float4 position : SV_POSITION;
  float2 texcoord : TEXCOORD;
  float4 normal : NORMAL;
  float3 light0 : LIGHT0;
};

VOut VSTransform(float3 position : POSITION, 
                 float2 texcoord : TEXCOORD, 
                 float3 normal : NORMAL) {
  VOut output;
  float4x4 PV = mul(m_projection, m_view);
  float4x4 VM = mul(m_view, m_model);
  float4x4 PVM = mul(PV, m_model);

  output.position = mul(PVM, float4(position, 1.0));
  output.normal = mul(VM, float4(normal, 0.0));
  output.texcoord = texcoord;
  output.light0 = mul(VM, float4(0, 1, 1, 0)).xyz;

  return output;
}
