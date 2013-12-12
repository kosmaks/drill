#include "../dxheaders.h"
#include "dxshader.h"

using namespace drill;

void dxshader::_link_to(linker *l) {
  if (type == DXSHADER_VERTEX) {
    handle->devcon->VSSetShader(pVS, 0, 0);
    D3D11_INPUT_ELEMENT_DESC ied[] = {
      { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    handle->dev->CreateInputLayout(ied, 1, blob->GetBufferPointer(), blob->GetBufferSize(), &layout);
    handle->devcon->IASetInputLayout(layout);
  } else {
    handle->devcon->PSSetShader(pPS, 0, 0);
  }
}

void dxshader::compile(const std::string &path, dxshader::type_t type) {
  LOG_DEBUG("Compiling shader '" << path << "'");

  this->type = type;
  D3DX11CompileFromFile(path.c_str(), 
                        0, 0, 
                        (type == DXSHADER_VERTEX) ? "VShader" : "PShader", 
                        (type == DXSHADER_VERTEX) ? "vs_5_0" : "ps_5_0",
                        0, 0, 0,
                        &blob,
                        0, 0);

  if (type == DXSHADER_VERTEX) {
    handle->dev->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &pVS);
  } else {
    handle->dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &pPS);
  }
}
