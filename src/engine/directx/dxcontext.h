#pragma once

#include "dxheaders.h"
#include "engine/virtual/context.h"

namespace drill {
  typedef struct {
    ID3D11Device *dev;
    ID3D11DeviceContext *devcon;
  } dxhandle_t;

  typedef struct {
    std::function<void(WPARAM, LPARAM)> keydown;
    std::function<void(WPARAM, LPARAM)> keyup;
  } winapi_router_t;

  class dxcontext : public context {
  public:
    dxcontext(const std::string &title = "DirectX Context", 
              int width=1200, 
              int height=800);
    ~dxcontext();
    void load();
    void swap_buffers();
    void clear_screen();
    void defined() {}
    inline uint32_t get_width() { return _width; }
    inline uint32_t get_height() { return _height; }

    void* info(size_t hash);

  private:
    int _width, _height;
    HWND h_wnd;
    HINSTANCE h_instance;
    MSG msg;

    dxhandle_t handle;
    winapi_router_t router;

    IDXGISwapChain *swapchain;
    ID3D11RenderTargetView *backbuffer;
    ID3D11DepthStencilView* dsv;

    void init_d3d();
  };
}
