#include "engine/core/app.h"
#include "dxcompiler.h"

using namespace drill;

dxcompiler::~dxcompiler() {
  for (std::pair<void*, dxc_object*> pair : _pool) {
    delete pair.second; 
  }
}

void dxcompiler::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
}

c_object *dxcompiler::compile(object &obj) {
  dxc_object *r = _pool[&obj];
  if (r == nullptr) { _pool[&obj] = r = new dxc_object(); }
  r->handle = handle;
  r->count = obj.triangles.count;

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(vector3_t) * obj.triangles.count;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  LOG_DEBUG("Creating DirectX buffer");
  handle->dev->CreateBuffer(&bd, NULL, &r->buffer);

  D3D11_MAPPED_SUBRESOURCE ms;
  handle->devcon->Map(r->buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
  memcpy(ms.pData, obj.triangles.vertices, obj.triangles.count * sizeof(vector3_t));
  handle->devcon->Unmap(r->buffer, NULL);

  return r;
}

void dxc_object::render() {
  UINT stride = sizeof(vector3_t);
  UINT offset = 0;
  handle->devcon->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
  handle->devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  handle->devcon->Draw(count, 0);
}
