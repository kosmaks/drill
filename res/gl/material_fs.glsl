#version 410

uniform float timer;
uniform mat4 m_view;
uniform mat4 m_model;
uniform vec4 color;
uniform sampler2D basic_texture;

in vec3 vertex;
in vec2 texcoord;
in vec3 normal;

// fixed point light properties
vec3 ls_position  = vec3 (0, 15, 5);
/*vec3 ls_position  = vec3 (0, 0, 0);*/
vec3 ls_specular = vec3 (1.0, 1.0, 1.0); // white specular colour
vec3 ls_diffuse = vec3 (0.7, 0.7, 0.7); // dull white diffuse light colour
vec3 ls_ambient = vec3 (0.5, 0.5, 0.5); // grey ambient colour
  
// surface reflectance
vec3 mat_specular = vec3 (1.0, 1.0, 1.0); // fully reflect specular light
vec3 mat_diffuse = vec3 (1.0, 1.0, 1.0); // orange diffuse surface reflectance
vec3 mat_ambient = vec3 (1.0, 1.0, 1.0); // fully reflect ambient light
float specular_exponent = 2.0; // specular 'power'

out vec4 frag_color;

void main() {
  /*vec4 res = vec4(1, 1, 1, 1);//texture(basic_texture, texcoord.st);*/
  vec4 res = texture(basic_texture, texcoord.st);
  vec3 lse_position = (m_view * vec4(ls_position, 1.0)).xyz;

  vec3 direction_to_lse = normalize(lse_position - vertex);
  float diffuse_dot = max(dot(direction_to_lse, normal), 0);

  vec3 reflection_eye = reflect(-direction_to_lse, normal);
  vec3 surface_to_viewer_eye = normalize(-vertex);
  float specular_dot = max(dot(reflection_eye, surface_to_viewer_eye), 0);
  float specular_factor = pow(specular_dot, specular_exponent);

  vec3 ambient = ls_ambient * mat_ambient;
  vec3 diffuse = ls_diffuse * mat_diffuse * diffuse_dot;
  vec3 specular = ls_specular * mat_specular * specular_factor; 

  vec4 color = vec4(ambient + diffuse + specular, 1.0);
  /*vec4 color = vec4(1, 1, 1, 1);*/
  frag_color = color * res;
  /*frag_color = vec4(0.5 + 0.5 * (normal), 1.0);*/
}
