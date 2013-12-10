#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "engine/virtual/context.h"

namespace drill {
  class dxcontext : public context {
  public:
    dxcontext(const std::string &title = "DirectX Context", 
              int width=640, 
              int height=480);
    ~dxcontext();
    void load();
    void swap_buffers();

  private:
    int _width, _height;
    HWND h_wnd;
    HINSTANCE h_instance;
    MSG msg;
    IDXGISwapChain *swapchain;
    ID3D11Device *dev;
    ID3D11DeviceContext *devcon;
    ID3D11RenderTargetView *backbuffer;

    void init_d3d();
  };
}
