#include <assert.h>
#include <stdio.h>
#include "graphics.h"

ID3D11Device* p_Device = NULL;
IDXGISwapChain* p_SwapChain = NULL;
ID3D11DeviceContext* p_DeviceContext = NULL;


void Graphics_Init(HWND hwnd) {

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
 {
    RECT rc;
    GetClientRect(hwnd, &rc);

    sd.BufferCount = 1;
    sd.BufferDesc.Width = rc.right - rc.left;
    sd.BufferDesc.Height = rc.bottom - rc.top;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0; // Assigning 1 here craches the program. Why?
    sd.Windowed = TRUE;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;
 }

UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

HRESULT hr = D3D11CreateDeviceAndSwapChain(
    NULL,
    D3D_DRIVER_TYPE_HARDWARE,
    NULL,
    createDeviceFlags,
    NULL,
    0,
    D3D11_SDK_VERSION,
    &sd,
    &p_SwapChain,
    &p_Device,
    NULL,
    &p_DeviceContext
);

assert(p_SwapChain != NULL);

if (FAILED(hr)) {
    printf("D3D11CreateDeviceAndSwapChain failed with error code: 0x%08X\n", hr);
    getchar();
    return;
}

};

typedef HRESULT (WINAPI *PresentFunc)(IDXGISwapChain*, UINT, UINT);

void Graphics_EndFrame() {

    assert(p_SwapChain != NULL);
    PresentFunc pPresent = p_SwapChain->lpVtbl->Present;
    HRESULT hr = pPresent(p_SwapChain, 1u, 0u);
}