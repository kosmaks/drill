#include "engine/core/app.h"
#include "dxcontext.h"

using namespace drill;

LRESULT CALLBACK WindowProc(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param) {
    switch(message) {
    }

    return DefWindowProc(h_wnd, message, w_param, l_param);
}

dxcontext::dxcontext(const std::string &title, int width, int height) {
  _width = width;
  _height = height;
  h_instance = GetModuleHandle(NULL);

  WNDCLASSEX wc;
  ZeroMemory(&wc, sizeof(WNDCLASSEX));
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = h_instance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpszClassName = "WindowClass1";

  RegisterClassEx(&wc);

  h_wnd = CreateWindowEx(NULL,
                         "WindowClass1",
                         title.c_str(),
                         WS_OVERLAPPEDWINDOW,
                         300, // x pos
                         300, // y pos
                         width,
                         height,
                         NULL,
                         NULL,
                         h_instance,
                         NULL);

}

dxcontext::~dxcontext() {
  swapchain->Release();
  backbuffer->Release();
  dev->Release();
  devcon->Release();
}

void dxcontext::load() {
  ShowWindow(h_wnd, SW_SHOW);
  init_d3d();
}

void dxcontext::swap_buffers() {
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
  swapchain->Present(0, 0);
}

void dxcontext::init_d3d() {
  LOG_INFO("Initializing DirectX");

  DXGI_SWAP_CHAIN_DESC scd;
  ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
  scd.BufferCount = 1;
  scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
  scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
  scd.OutputWindow = h_wnd;                               // the window to be used
  scd.SampleDesc.Count = 4;                               // how many multisamples
  scd.Windowed = true;                                    // windowed/full-screen mode

  D3D11CreateDeviceAndSwapChain(NULL,
                                D3D_DRIVER_TYPE_HARDWARE,
                                NULL, NULL, NULL, NULL,
                                D3D11_SDK_VERSION,
                                &scd,
                                &swapchain,
                                &dev,
                                NULL,
                                &devcon);

  LOG_DEBUG("Setting up render target");
  ID3D11Texture2D *p_back_buffer;
  swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_back_buffer);
  dev->CreateRenderTargetView(p_back_buffer, NULL, &backbuffer);
  p_back_buffer->Release();
  devcon->OMSetRenderTargets(1, &backbuffer, NULL);

  LOG_DEBUG("Setting up viewport");
  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = _width;
  viewport.Height = _height;
  devcon->RSSetViewports(1, &viewport);
}
