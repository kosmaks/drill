#include "dxbridge_object.h"

using namespace drill;

dxbridge_object::~dxbridge_object() {
  if (colored_vertices != nullptr) { delete colored_vertices; }
}

void dxbridge_object::compile() {
  LOG_INFO("Compiling DirectX object");

  auto devcon = current_context->get_devcon();
  auto device = current_context->get_device();

  uint32_t count = current_target->triangles.count;
  colored_vertices = new vector4_t[count];
  for (uint32_t i = 0; i < count; ++i) {
    vector3_t &vec = current_target->triangles.vertices[i];
    colored_vertices[i] = { 
      vec.x, vec.y, vec.z, 
      D3DXCOLOR(current_target->color.x, 
                current_target->color.y, 
                current_target->color.z, 1.0f) };
  }

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(vector4_t) * count;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  device->CreateBuffer(&bd, NULL, &p_vbuffer);

  D3D11_MAPPED_SUBRESOURCE ms;
  devcon->Map(p_vbuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
  memcpy(ms.pData, colored_vertices, count); // might be here
  devcon->Unmap(p_vbuffer, NULL);
}

void dxbridge_object::draw() {
}
