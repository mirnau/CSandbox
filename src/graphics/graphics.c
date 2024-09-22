#include <assert.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgiformat.h>
#include <stdio.h>
#include <d3dcompiler.h>
#include <winnt.h>
#include "graphics.h"
#include "../../include/redefined_nuklear.h"
#include "../math/typedef.h"

#define SAFE_RELEASE(P) if(P){ P->lpVtbl->Release(P); P = NULL;}

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024

ID3D11Device* pp_Device = NULL;
IDXGISwapChain* pp_SwapChain = NULL;
ID3D11DeviceContext* pp_DeviceContext = NULL;
ID3D11RenderTargetView* pp_Target = NULL;

void Graphics_Init(HWND hwnd) {

    struct nk_context *ctx;

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));

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

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL, 
        D3D11_CREATE_DEVICE_DEBUG, //For debug
        NULL,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &pp_SwapChain,
        &pp_Device,
        NULL,
        &pp_DeviceContext
    );

    LogError(D3D11CreateDeviceAndSwapChain, hr);

        ID3D11Resource* pp_BackBuffer;

    float clearColor[4] = { 0.392f, 0.584f, 0.929f, 1.0f };

    pp_SwapChain->lpVtbl->GetBuffer(pp_SwapChain, 0, &IID_ID3D11Resource, (void**)&pp_BackBuffer);
    pp_Device->lpVtbl->CreateRenderTargetView(pp_Device, pp_BackBuffer, NULL, &pp_Target);
    pp_DeviceContext->lpVtbl->ClearRenderTargetView(pp_DeviceContext, pp_Target, clearColor);
    pp_BackBuffer->lpVtbl->Release(pp_BackBuffer);
};

void ClearBuffer(float r, float g, float b) {

    const float color[] = {r,g,b, 1.0f};
    pp_DeviceContext->lpVtbl->ClearRenderTargetView(pp_DeviceContext, pp_Target, color);
}

HRESULT Graphics_EndFrame() {
    return pp_SwapChain->lpVtbl->Present(pp_SwapChain, 1u, 0u);
}

void UpdateShaders() {

    const Vector2 vertecies[] = {
        {0.0f, 0.5f, 255, 0 ,0, 0},
        {0.5f, -0.5f, 0 , 255, 0, 0},
        {-0.5f,-0.5f, 0, 0, 255, 0},
        {-0.3f, 0.3f, 0, 255, 0, 0},
        {0.3f, 0.3f, 0, 0, 255, 0},
        {0.0f, -0.8f, 255, 0, 0, 0},
    };

    ID3D11Buffer* pp_VertexBuffer;
    D3D11_BUFFER_DESC bd;
    memset(&bd, 0, sizeof(bd));
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = sizeof(vertecies);
    bd.StructureByteStride = sizeof(Vector2);
    D3D11_SUBRESOURCE_DATA sd;
    memset(&sd, 0, sizeof(sd));
    sd.pSysMem = vertecies;

    const u32 stride = sizeof(Vector2);
    const u32 offset = 0u;

    // NOTE: Bind Vertex Buffer
    pp_Device->lpVtbl->CreateBuffer(pp_Device, &bd, &sd, &pp_VertexBuffer);
    pp_DeviceContext->lpVtbl->IASetVertexBuffers(pp_DeviceContext, 0u, 1u, &pp_VertexBuffer, &stride, &offset);

    const u16 indices[] ={
        0,1,2,
        0,2,3,
        0,4,1,
        2,1,5,
    };
    
    ID3D11Buffer* pp_IndexBuffer;
    D3D11_BUFFER_DESC ibd;
    memset(&ibd, 0, sizeof(ibd));
    ibd.ByteWidth = sizeof(indices);
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0u;
    ibd.MiscFlags = 0u;
    ibd.StructureByteStride = sizeof(u16);
    D3D11_SUBRESOURCE_DATA isd;
    memset(&isd, 0, sizeof(isd));
    isd.pSysMem = indices;

    // NOTE: Bind Index Buffer
    pp_Device->lpVtbl->CreateBuffer(pp_Device, &ibd, &isd, &pp_IndexBuffer);
    pp_DeviceContext->lpVtbl->IASetIndexBuffer(pp_DeviceContext, pp_IndexBuffer, DXGI_FORMAT_R16_UINT, 0u);

    pp_VertexBuffer->lpVtbl->Release(pp_VertexBuffer);
    
    //NOTE: Pixelshader Start here:
    ID3D11PixelShader* pp_PixelShader = NULL;
    ID3DBlob* pp_Blob = NULL;
    
    HRESULT hr = D3DReadFileToBlob(
        L"src\\graphics\\pixel_shader.cso", 
        &pp_Blob);

    LogError(ID3D11PixelShader, hr);
    if(FAILED(hr)) {
        SAFE_RELEASE(pp_Blob);
        return;
    }

    LogError(D3DReadFileToBlob, hr);
    hr = pp_Device->lpVtbl->CreatePixelShader(
        pp_Device,
        pp_Blob->lpVtbl->GetBufferPointer(pp_Blob),
        pp_Blob->lpVtbl->GetBufferSize(pp_Blob),
        NULL,
        &pp_PixelShader
    );


    if(FAILED(hr)) {
        SAFE_RELEASE(pp_Blob);
        SAFE_RELEASE(pp_PixelShader);
        return;
    }
 
    //Pixel Shader // Bidning PixelShader
    pp_DeviceContext->lpVtbl->PSSetShader(pp_DeviceContext, pp_PixelShader, NULL, 0u);

    //NOTE: Vertexshader starts here:
    ID3D11VertexShader* pp_VertexShader = NULL;

    hr = D3DReadFileToBlob(
    L"src\\graphics\\vertex_shader.cso",
        &pp_Blob);

    LogError(D3D3ReadFileToBlob, hr);
 
    if(FAILED(hr)) {
        SAFE_RELEASE(pp_Blob);
        SAFE_RELEASE(pp_PixelShader);
        return;
    }
    
    hr = pp_Device->lpVtbl->CreateVertexShader(
        pp_Device, 
        pp_Blob->lpVtbl->GetBufferPointer(pp_Blob),
        pp_Blob->lpVtbl->GetBufferSize(pp_Blob),
        NULL,
        &pp_VertexShader
    );

    if(FAILED(hr)) {
        SAFE_RELEASE(pp_Blob)
        SAFE_RELEASE(pp_PixelShader);
        SAFE_RELEASE(pp_VertexShader);
        return;
    }
      // Vertex Shader // Binding Vertex Shader
    pp_DeviceContext->lpVtbl->VSSetShader(pp_DeviceContext, pp_VertexShader, ((void*)0), 0u);
    
    ID3D11InputLayout* pp_InputLayout;
    const D3D11_INPUT_ELEMENT_DESC ied[] = {
        {
            "Position",
            0u,
            DXGI_FORMAT_R32G32_FLOAT,
            0u,
            0u,
            D3D11_INPUT_PER_VERTEX_DATA,
            0u
        },
        {
            "Color",
            0u,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            0,
            8u,
            D3D11_INPUT_PER_VERTEX_DATA,
            0u
        }
    };

    hr = pp_Device->lpVtbl->CreateInputLayout(
        pp_Device,
        ied,
        ARRAYSIZE(ied),
        pp_Blob->lpVtbl->GetBufferPointer(pp_Blob),
        pp_Blob->lpVtbl->GetBufferSize(pp_Blob),
        &pp_InputLayout
    );

    if(FAILED(hr)) {
    SAFE_RELEASE(pp_Blob)
    SAFE_RELEASE(pp_VertexShader);
    SAFE_RELEASE(pp_PixelShader);
    SAFE_RELEASE(pp_InputLayout);
        return;
    }

    LogError(ID3D11InputLayout, hr);

    pp_DeviceContext->lpVtbl->IASetInputLayout(pp_DeviceContext, pp_InputLayout);

    pp_DeviceContext->lpVtbl->OMSetRenderTargets(pp_DeviceContext, 1u, &pp_Target, NULL);

    pp_DeviceContext->lpVtbl->IASetPrimitiveTopology(pp_DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    D3D11_VIEWPORT vp;
    vp.Width = 800;
    vp.Height = 600;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pp_DeviceContext->lpVtbl->RSSetViewports(pp_DeviceContext,1u, &vp);
    
    //u32 vertexCount = (sizeof(vertecies) / sizeof(vertecies[0]));
    u32 indexCount = (sizeof(indices) / sizeof(indices[0]));
    pp_DeviceContext->lpVtbl->DrawIndexed(pp_DeviceContext, indexCount,0u, 0u);

    SAFE_RELEASE(pp_Blob)
    SAFE_RELEASE(pp_VertexShader);
    SAFE_RELEASE(pp_PixelShader);
    SAFE_RELEASE(pp_InputLayout);
}

void ReleaseOnAppExit() {
    SAFE_RELEASE(pp_DeviceContext);
    SAFE_RELEASE(pp_SwapChain);
    SAFE_RELEASE(pp_Target);
}
