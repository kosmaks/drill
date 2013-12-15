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

  r->triangles_count = obj.get_triangles_count();
  r->points_count = obj.get_points_count();

  gen_buffer(&r->triangles, obj.get_triangles(), r->triangles_count);
  gen_buffer(&r->points, obj.get_points(), r->points_count);

  return r;
}

void dxc_object::render() {
  draw(triangles, triangles_count, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  draw(points, points_count, D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
}

void dxc_object::free() {
  if (triangles != nullptr) triangles->Release();
  if (points != nullptr) points->Release();
}

void dxc_object::draw(ID3D11Buffer *buffer, uint32_t count, D3D10_PRIMITIVE_TOPOLOGY type) {
  if (buffer != nullptr && count > 0) {
    UINT stride = sizeof(vertex_t);
    UINT offset = 0;
    handle->devcon->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
    handle->devcon->IASetPrimitiveTopology(type);
    handle->devcon->Draw(count, 0);
  }
}

void dxcompiler::gen_buffer(ID3D11Buffer **output, vertex_t *input, uint32_t count) {
  if (count > 0) {
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(vertex_t) * count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    LOG_DEBUG("Creating DirectX buffer");
    handle->dev->CreateBuffer(&bd, NULL, output);
    LOG_DEBUG("r->buffer = " << *output);

    D3D11_MAPPED_SUBRESOURCE ms;
    handle->devcon->Map(*output, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
    memcpy(ms.pData, input, count * sizeof(vertex_t));
    handle->devcon->Unmap(*output, NULL);
  } else {
    *output = nullptr;
  }
}
