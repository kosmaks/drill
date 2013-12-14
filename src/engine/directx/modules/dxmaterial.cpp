#include "engine/core/config.h"
#include "dxmaterial.h"

using namespace drill;

void dxmaterial::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
}

void dxmaterial::init() {
  _color = { 1.0, 1.0, 1.0, 1.0 };
  compile(CFG_DX_MATERIAL_PS_PATH, "PSMaterial", DXSHADER_PIXEL);

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(_color);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  handle->dev->CreateBuffer(&bd, NULL, &buffer);
}

material& dxmaterial::use_texture(const texture &texture) {

  D3D11_TEXTURE2D_DESC desc;
  desc.Width = texture.get_width();
  desc.Height = texture.get_height();
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;
  desc.Usage = D3D11_USAGE_IMMUTABLE;
  desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA res;
  res.pSysMem = texture.get_data();
  res.SysMemPitch = (UINT) (texture.get_format() * texture.get_width());
  res.SysMemSlicePitch = (UINT) (texture.get_format() * texture.get_width() * texture.get_height());

  D3D11_SAMPLER_DESC samp;
  ZeroMemory(&samp, sizeof(D3D11_SAMPLER_DESC));
  samp.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  samp.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  samp.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  samp.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  samp.ComparisonFunc = D3D11_COMPARISON_NEVER;
  samp.MinLOD = 0;
  samp.MaxLOD = D3D11_FLOAT32_MAX;

  if (FAILED(handle->dev->CreateTexture2D(&desc, &res, &_texture))) {
    LOG_ERROR("Failed to create texture");
    return *this;
  }

  if (FAILED(handle->dev->CreateShaderResourceView(_texture, NULL, &texture_srv))) {
    LOG_ERROR("Failed to create texture resource");
  }

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
  handle->devcon->PSSetShaderResources(0, 1, &texture_srv);
}
