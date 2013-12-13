#include "engine/core/config.h"
#include "dxmaterial.h"

using namespace drill;

void dxmaterial::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
}

void dxmaterial::init() {
  compile(CFG_DX_COLOR_PS_PATH, "PSColor", DXSHADER_PIXEL);

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(_color);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  handle->dev->CreateBuffer(&bd, NULL, &buffer);
}

material& dxmaterial::use_texture(const texture &texture) {
  return *this;
}

material& dxmaterial::color(const vector4_t &color) {
  _color = color;
  return *this;
}

void dxmaterial::ready() {
  D3D11_MAPPED_SUBRESOURCE ms;
  handle->devcon->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
  memcpy(ms.pData, &_color, sizeof(_color));
  handle->devcon->Unmap(buffer, NULL);

  ID3D11Buffer *buffers[] = { buffer };
  handle->devcon->PSSetConstantBuffers(0, 1, &buffer);
}
