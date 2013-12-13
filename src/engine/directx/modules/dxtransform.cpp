#include "engine/core/config.h"
#include "dxtransform.h"

#define TO_RAD(x) (3.14*(x)/180)

using namespace drill;

void dxtransform::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
}

void dxtransform::init() {
  compile(CFG_DX_TRANSFORM_VS_PATH, DXSHADER_VERTEX);

  model_identity();
  projection_identity();
  view_identity();

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(state_t);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  handle->dev->CreateBuffer(&bd, NULL, &buffer);
}

transform& dxtransform::model_identity() {
  D3DXMatrixIdentity(&state.m_model);
  return *this;
}

transform& dxtransform::projection_identity() {
  D3DXMatrixIdentity(&state.m_projection);
  return *this;
}

transform& dxtransform::view_identity() {
  D3DXMatrixIdentity(&state.m_view);
  return *this;
}

transform& dxtransform::model_translate(const vector3_t &v) {
  D3DXMATRIX translation, tt;
  D3DXMatrixTranslation(&translation, v.x, v.y, v.z);
  D3DXMatrixTranspose(&tt, &translation);
  state.m_model *= tt;
  return *this;
}

transform& dxtransform::model_rotate(const vector4_t &v) {
  D3DXMATRIX rotate;
  D3DXMatrixRotationAxis(&rotate, (const D3DXVECTOR3*)&v, TO_RAD(v.w));
  state.m_model *= rotate;
  return *this;
}

transform& dxtransform::model_scale(const vector3_t &v) {
  D3DXMATRIX scaling;
  D3DXMatrixScaling(&scaling, v.x, v.y, v.z);
  state.m_model *= scaling;
  return *this;
}

transform& dxtransform::projection_translate(const vector3_t &v) {
  D3DXMATRIX translation, tt;
  D3DXMatrixTranslation(&translation, v.x, v.y, v.z);
  D3DXMatrixTranspose(&tt, &translation);
  state.m_projection *= tt;
  return *this;
}

transform& dxtransform::projection_rotate(const vector4_t &v) {
  D3DXMATRIX rotate;
  D3DXMatrixRotationAxis(&rotate, (const D3DXVECTOR3*)&v, TO_RAD(v.w));
  state.m_projection *= rotate;
  return *this;
}

transform& dxtransform::projection_scale(const vector3_t &v) {
  D3DXMATRIX scaling;
  D3DXMatrixScaling(&scaling, v.x, v.y, v.z);
  state.m_projection *= scaling;
  return *this;
}

transform& dxtransform::view_translate(const vector3_t &v) {
  D3DXMATRIX translation, tt;
  D3DXMatrixTranslation(&translation, v.x, v.y, v.z);
  D3DXMatrixTranspose(&tt, &translation);
  state.m_view *= tt;
  return *this;
}

transform& dxtransform::view_rotate(const vector4_t &v) {
  D3DXMATRIX scaling;
  D3DXMatrixScaling(&scaling, v.x, v.y, v.z);
  state.m_view *= scaling;
  return *this;
}

transform& dxtransform::view_scale(const vector3_t &v) {
  D3DXMATRIX scaling;
  D3DXMatrixScaling(&scaling, v.x, v.y, v.z);
  state.m_view *= scaling;
  return *this;
}

void dxtransform::ready() {
  D3D11_MAPPED_SUBRESOURCE ms;
  handle->devcon->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
  state_t *s = (state_t*)ms.pData;
  s->m_model = state.m_model;
  s->m_projection = state.m_projection;
  s->m_view = state.m_view;
  handle->devcon->Unmap(buffer, NULL);

  ID3D11Buffer *buffers[] = { buffer };
  handle->devcon->VSSetConstantBuffers(0, 1, &buffer);
}
