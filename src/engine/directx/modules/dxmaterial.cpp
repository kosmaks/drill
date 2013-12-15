#include "engine/core/config.h"
#include "dxmaterial.h"

using namespace drill;

dxmaterial::~dxmaterial() {
  for (std::pair<void*, dxc_texture*> kv : _pool) {
    delete kv.second;
  }
}

void dxmaterial::defined() {
  handle = REQUIRE(drill::context).get_info<dxhandle_t>();
  compile(CFG_DX_MATERIAL_PS_PATH, "PSMaterial", DXSHADER_PIXEL);

  _color = { 1.0, 1.0, 1.0, 1.0 };

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(_color);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  handle->dev->CreateBuffer(&bd, NULL, &buffer);
}

c_texture* dxmaterial::compile_texture(texture &texture) {

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

  if (FAILED(handle->dev->CreateTexture2D(&desc, &res, &_texture))) {
    LOG_ERROR("Failed to create texture");
    return nullptr;
  }

  if (FAILED(handle->dev->CreateShaderResourceView(_texture, NULL, &texture_srv))) {
    LOG_ERROR("Failed to create texture resource");
  }

  auto ct = new dxc_texture(handle->devcon, texture_srv);
  if (_pool[&texture]) delete _pool[&texture];
  return (_pool[&texture] = ct);
}

material& dxmaterial::color(const vector4_t &color) {
  _color = color;
  return *this;
}

material& dxmaterial::use_texture(c_texture *c_texture) {
  c_texture->use();
  return *this;
}

void dxmaterial::flush() {
  D3D11_MAPPED_SUBRESOURCE ms;
  handle->devcon->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
  memcpy(ms.pData, &_color, sizeof(_color));
  handle->devcon->Unmap(buffer, NULL);

  ID3D11Buffer *buffers[] = { buffer };
  handle->devcon->PSSetConstantBuffers(0, 1, &buffer);
}

dxc_texture::dxc_texture(ID3D11DeviceContext *d, ID3D11ShaderResourceView *t) :
  c_texture(), devcon(d), texture_srv(t) {}

void dxc_texture::use() { 
  devcon->PSSetShaderResources(0, 1, &texture_srv);
}
