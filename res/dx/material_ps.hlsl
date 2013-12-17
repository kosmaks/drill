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

  float3 ls_position  = float3 (0, 15, 5);
  float3 ls_specular = float3 (1.0, 1.0, 1.0); // white specular colour
  float3 ls_diffuse = float3 (0.7, 0.7, 0.7); // dull white diffuse light colour
  float3 ls_ambient = float3 (0.5, 0.5, 0.5); // grey ambient colour
    
  // surface reflectance
  float3 mat_specular = float3 (1.0, 1.0, 1.0); // fully reflect specular light
  float3 mat_diffuse = float3 (1.0, 1.0, 1.0); // orange diffuse surface reflectance
  float3 mat_ambient = float3 (1.0, 1.0, 1.0); // fully reflect ambient light
  float specular_exponent = 2.0; // specular 'power'

  float3 lse_position = (float4(ls_position, 1.0)).xyz;

  float3 direction_to_lse = normalize(lse_position - position.xyz);
  float diffuse_dot = max(dot(direction_to_lse, normal), 0);

  float3 reflection_eye = reflect(-direction_to_lse, normal);
  float3 surface_to_viewer_eye = normalize(-position.xyz);
  float specular_dot = max(dot(reflection_eye, surface_to_viewer_eye), 0);
  float specular_factor = pow(specular_dot, specular_exponent);

  float3 ambient = ls_ambient * mat_ambient;
  float3 diffuse = ls_diffuse * mat_diffuse * diffuse_dot;
  float3 specular = ls_specular * mat_specular * specular_factor; 

  float4 intensity = float4(ambient + diffuse + specular, 1.0);
  float4 color = intensity * buffer * basic_texture.Sample(linear_sampler, texcoord);

  return color;
}
