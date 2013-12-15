#include "engine/core/config.h"
#include "dxcolor.h"

using namespace drill;

void dxcolor::defined() {
  handle = require<drill::context>().get_info<dxhandle_t>();
  compile(CFG_DX_COLOR_PS_PATH, "PSColor", DXSHADER_PIXEL);

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(value);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  handle->dev->CreateBuffer(&bd, NULL, &buffer);
}

void dxcolor::ready() {
  D3D11_MAPPED_SUBRESOURCE ms;
  handle->devcon->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
  memcpy(ms.pData, &value, sizeof(value));
  handle->devcon->Unmap(buffer, NULL);

  ID3D11Buffer *buffers[] = { buffer };
  handle->devcon->PSSetConstantBuffers(0, 1, &buffer);
}
