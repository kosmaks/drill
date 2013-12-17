#include "engine/core/app.h"
#include "dxcontext.h"

using namespace drill;

#define DXD(x) { auto k = (x); if (FAILED(k)) LOG_ERROR("HRESULT = FAILED"); }

LRESULT CALLBACK WindowProc(HWND h_wnd, UINT message, WPARAM w_param, LPARAM l_param) {
  winapi_router_t *router = (winapi_router_t*)GetWindowLongPtr(h_wnd, GWLP_USERDATA);

  switch(message) {
    case WM_KEYDOWN: router->keydown(w_param, l_param); break;
    case WM_KEYUP: router->keyup(w_param, l_param); break;
    case WM_LBUTTONDOWN: router->mouse(0, 1); break;
    case WM_LBUTTONUP: router->mouse(0, 0); break;
    case WM_RBUTTONDOWN: router->mouse(1, 1); break;
    case WM_RBUTTONUP: router->mouse(1, 0); break;
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
  wc.hIcon = LoadIcon(h_instance, "IDI_ICON1");

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

  SetWindowLongPtr(h_wnd, GWLP_USERDATA, (LONG)&router);
}

dxcontext::~dxcontext() {
  swapchain->Release();
  backbuffer->Release();
  handle.dev->Release();
  handle.devcon->Release();
}

void dxcontext::load() {
  ShowWindow(h_wnd, SW_SHOW);
  init_d3d();
}

void dxcontext::clear_screen() {
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  handle.devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	handle.devcon->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void dxcontext::swap_buffers() {
  swapchain->Present(0, 0);
}

void* dxcontext::info(size_t hash) {
  if (hash == typeid(dxhandle_t).hash_code()) {
    return &handle;
  } else if (hash == typeid(winapi_router_t).hash_code()) {
    return &router;
  } else {
    return nullptr;
  }
}

void dxcontext::init_d3d() {
  LOG_INFO("Initializing DirectX");

  DXGI_SWAP_CHAIN_DESC scd;
  ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

  scd.BufferCount = 2;
  scd.BufferDesc.Width = _width;                          // use 32-bit color
  scd.BufferDesc.Height = _height;                        // use 32-bit color
  scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
  scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used

  scd.SampleDesc.Quality = 0;
  scd.SampleDesc.Count = 1;                               // how many multisamples

  scd.OutputWindow = h_wnd;                               // the window to be used
  scd.Windowed = true;                                    // windowed/full-screen mode

  D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
  DXD(D3D11CreateDeviceAndSwapChain(NULL,
                                D3D_DRIVER_TYPE_HARDWARE,
                                NULL, 
                                0, 
                                &featureLevel, 
                                1,
                                D3D11_SDK_VERSION,
                                &scd,
                                &swapchain,
                                &handle.dev,
                                NULL,
                                &handle.devcon));

  LOG_DEBUG("Setting up render target");
  ID3D11Texture2D *p_back_buffer;
  DXD(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_back_buffer));
  handle.dev->CreateRenderTargetView(p_back_buffer, NULL, &backbuffer);
  p_back_buffer->Release();

  LOG_DEBUG("Setting up depth-stencil buffer");
  D3D11_TEXTURE2D_DESC descDepth;
  descDepth.Width = _width;
  descDepth.Height = _height;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;
  ID3D11Texture2D* pDS = NULL;
  handle.dev->CreateTexture2D(&descDepth, NULL, &pDS);

  D3D11_DEPTH_STENCIL_DESC dsDesc;
  dsDesc.DepthEnable = true;
  dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
  dsDesc.StencilEnable = true;
  dsDesc.StencilReadMask = 0xFF;
  dsDesc.StencilWriteMask = 0xFF;
  dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
  dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
  dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
  dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
  ID3D11DepthStencilState * pDSState;
  handle.dev->CreateDepthStencilState(&dsDesc, &pDSState);
  handle.devcon->OMSetDepthStencilState(pDSState, 1);

  LOG_DEBUG("Binding depth-stencil resource");
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  descDSV.Format = descDepth.Format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  descDSV.Flags = 0;
  handle.dev->CreateDepthStencilView(pDS, &descDSV, &dsv);
  handle.devcon->OMSetRenderTargets(1, &backbuffer, dsv);

  LOG_DEBUG("Configuring alpha blending");
  D3D11_BLEND_DESC blend;
  ZeroMemory(&blend, sizeof(D3D11_BLEND_DESC));
  blend.RenderTarget[0].BlendEnable = TRUE;
  blend.RenderTarget[0].RenderTargetWriteMask = 0x0F;
  blend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  blend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
  blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  ID3D11BlendState* blendstate = NULL;
  handle.dev->CreateBlendState(&blend, &blendstate);
  handle.devcon->OMSetBlendState(blendstate, NULL, 0xFFFFFF);

  LOG_DEBUG("Setting up viewport");
  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = _width;
  viewport.Height = _height;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;
  handle.devcon->RSSetViewports(1, &viewport);

  LOG_DEBUG("Setting up rastarizer");
  ID3D11RasterizerState *pRS;
  D3D11_RASTERIZER_DESC rasterizer;
  ZeroMemory(&rasterizer, sizeof(D3D11_RASTERIZER_DESC));
  rasterizer.CullMode = D3D11_CULL_NONE;
  rasterizer.FillMode = D3D11_FILL_SOLID;
  //rasterizer.FillMode = D3D11_FILL_WIREFRAME;
  rasterizer.FrontCounterClockwise = true;
  rasterizer.DepthBias = false;
  rasterizer.DepthBiasClamp = 0;
  rasterizer.SlopeScaledDepthBias = 0;
  rasterizer.DepthClipEnable = true;
  rasterizer.ScissorEnable = false;
  rasterizer.MultisampleEnable = false;
  rasterizer.AntialiasedLineEnable = true;
  handle.dev->CreateRasterizerState(&rasterizer, &pRS);
  handle.devcon->RSSetState(pRS);

}
