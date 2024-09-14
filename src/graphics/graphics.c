#include <assert.h>
#include <stdio.h>
#include <d3dcompiler.h>
#include "graphics.h"
#include "../../include/redefined_nuklear.h"
#include "../math/typedef.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024


ID3D11Device* p_Device = NULL;
IDXGISwapChain* p_SwapChain = NULL;
ID3D11DeviceContext* p_DeviceContext = NULL;
ID3D11RenderTargetView* p_Target = NULL;


void Graphics_Init(HWND hwnd) {

    struct nk_context *ctx;

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
    
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL, 
        D3D11_CREATE_DEVICE_DEBUG, //For debug
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

ID3D11Resource* p_BackBuffer;

float clearColor[4] = { 0.392f, 0.584f, 0.929f, 1.0f };

p_SwapChain->lpVtbl->GetBuffer(p_SwapChain, 0, &IID_ID3D11Resource, (void**)&p_BackBuffer);
p_Device->lpVtbl->CreateRenderTargetView(p_Device, p_BackBuffer, NULL, &p_Target);
p_DeviceContext->lpVtbl->ClearRenderTargetView(p_DeviceContext, p_Target, clearColor);
p_BackBuffer->lpVtbl->Release(p_BackBuffer);

};

typedef HRESULT (WINAPI *PresentFunc)(IDXGISwapChain*, UINT, UINT);

HRESULT Graphics_EndFrame() {
     return p_SwapChain->lpVtbl->Present(p_SwapChain, 1u, 0u);
}

void Dummy() {

    const Vector2 vertecies[] = {
        {0.0f, 0.5f},
        {0.5f, -0.5f},
        {-0.5f, -0.5f}
    };

    ID3D11Buffer* vertexBuffer;
    
    D3D11_BUFFER_DESC bd;
    memset(&vertexBuffer, 0, sizeof(vertexBuffer));
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.CPUAccessFlags = FALSE;
    bd.MiscFlags = 0u;
    bd.ByteWidth = sizeof(vertecies);
    bd.StructureByteStride = sizeof(Vector2);
    D3D11_SUBRESOURCE_DATA sd;
    memset(&sd, 0, sizeof(sd));
    sd.pSysMem = vertecies;

    const u32 stride = sizeof(Vector2);
    const u32 offset = 0u;

    p_Device->lpVtbl->CreateBuffer(p_Device, &bd, &sd, &vertexBuffer);
    p_DeviceContext->lpVtbl->IASetVertexBuffers(p_DeviceContext, 0u, 1u, &vertexBuffer, &stride, &offset);



    // Vertex Shader

    ID3D11VertexShader* p_VertexShader;
    ID3DBlob* p_Blob;

    D3DReadFileToBlob(L"vertex_shader.cso", &p_Blob);
    p_Device->lpVtbl->CreateVertexShader(
        p_Device, 
        p_Blob->lpVtbl->GetBufferPointer(p_Blob),
        p_Blob->lpVtbl->GetBufferSize(p_Blob),
        NULL,
        &p_VertexShader
        );

    // Vertex Shader // Binding Vertex Shader
    p_DeviceContext->lpVtbl->VSSetShader(p_DeviceContext, p_VertexShader, ((void*)0), 0u);

    // Pixel Shader

    /*
    ID3D11PixelShader* p_PixelShader;
    D3DReadFileToBlob(L"pixel_shade.cso", &p_Blob);
    p_Device->lpVtbl->CreatePixelShader(
        p_Device,
        p_Blob->lpVtbl->GetBufferPointer(p_Blob),
        p_Blob->lpVtbl->GetBufferSize(p_Blob),
        NULL,
        &p_PixelShader
    );

    //Pixel Shader // Bidning PixelShader

    p_DeviceContext->lpVtbl->PSSetShader(p_DeviceContext, p_PixelShader, NULL, 0u);

    //Render Target

    p_DeviceContext->lpVtbl->OMSetRenderTargets(p_DeviceContext, 1u, &p_Target, NULL);
    */
    
    u32 vertexCount = (sizeof(vertecies) / sizeof(vertecies[0]));
    p_DeviceContext->lpVtbl->Draw(p_DeviceContext, vertexCount,0u);
}