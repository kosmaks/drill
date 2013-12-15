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
                  float3 normal : NORMAL,
                  float3 light0 : LIGHT0) : SV_TARGET {
  /*float intensity = dot(light0, normal.xyz);*/
  float intensity = 1;
  float4 color = intensity * buffer * basic_texture.Sample(linear_sampler, texcoord);
  color.w = 1.0;
  /*float4 color = float4((normal.xyz + float3(1, 1, 1)) / 2, 1);*/
  /*color = float4(normal.xyz, 1);*/

  return color;
}
