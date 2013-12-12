#pragma once

#include "dxheaders.h"
#include "engine/virtual/context.h"

namespace drill {
  typedef struct {
    ID3D11Device *dev;
    ID3D11DeviceContext *devcon;
  } dxhandle_t;

  class dxcontext : public context {
  public:
    dxcontext(const std::string &title = "DirectX Context", 
              int width=640, 
              int height=480);
    ~dxcontext();
    void load();
    void swap_buffers();
    void clear_screen();
    void defined() {}

    void* info(size_t hash);

  private:
    int _width, _height;
    HWND h_wnd;
    HINSTANCE h_instance;
    MSG msg;

    dxhandle_t handle;

    IDXGISwapChain *swapchain;
    ID3D11RenderTargetView *backbuffer;

    void init_d3d();
  };
}