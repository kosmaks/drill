cbuffer InputColor : register(b0) {
  float4 buffer;
};

Texture2D basic_texture;
SamplerState linear_sampler {
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


float4 PSMaterial(float4 position : SV_POSITION, 
                  float2 texcoord : TEXCOORD, 
                  float3 normal : NORMAL) : SV_TARGET {
  /*float intensity = dot(float3(0.0, 1.5, 0.0), normal.xyz);*/
  float intensity = 1;
  float4 color = intensity * buffer * basic_texture.Sample(linear_sampler, texcoord);
  return color;
  /*return buffer;*/
}
