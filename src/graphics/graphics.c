#include <assert.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgiformat.h>
#include <stdio.h>
#include <d3dcompiler.h>
#include <winnt.h>
#include <time.h>
#include <math.h>
#include "graphics.h"
#include "../window/window.h"
#include "../math/typedef.h"

#define SAFE_RELEASE(P) if(P){ P->lpVtbl->Release(P); P = NULL;}

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024

Graphics* Graphics_Create() {
    return calloc(1, sizeof(Graphics));
}

void Graphics_Init(Window* w) {

    Graphics* g = w->p_graphics;

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));

    RECT rc;
    GetClientRect(w->hWnd, &rc);

    sd.BufferCount = 1;
    sd.BufferDesc.Width = rc.right - rc.left;
    sd.BufferDesc.Height = rc.bottom - rc.top;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = w->hWnd;
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
        &g->pp_SwapChain,
        &g->pp_Device,
        NULL,
        &g->pp_DeviceContext
    );

    LogError(D3D11CreateDeviceAndSwapChain, hr);

        ID3D11Resource* pp_BackBuffer;

    float clearColor[4] = { 0.392f, 0.584f, 0.929f, 1.0f };

    g->pp_SwapChain->lpVtbl->GetBuffer(g->pp_SwapChain, 0, &IID_ID3D11Resource, (void**)&pp_BackBuffer);
    g->pp_Device->lpVtbl->CreateRenderTargetView(g->pp_Device, pp_BackBuffer, NULL, &g->pp_Target);
    g->pp_DeviceContext->lpVtbl->ClearRenderTargetView(g->pp_DeviceContext, g->pp_Target, clearColor);
    pp_BackBuffer->lpVtbl->Release(pp_BackBuffer);
};

void ClearBuffer(Graphics* gr, float r, float g, float b) {

    const float color[] = {r,g,b, 1.0f};
    gr->pp_DeviceContext->lpVtbl->ClearRenderTargetView(gr->pp_DeviceContext, gr->pp_Target, color);
}


HRESULT Graphics_EndFrame(Graphics * g) {
    return g->pp_SwapChain->lpVtbl->Present(g->pp_SwapChain, 1u, 0u);
}

float angle = 0.0f;
void UpdateShaders(Graphics* g) {

    const Vertex vertecies[] = {
        {{-1.f, -1.f, -1.f}, {255, 0,   0,  0}},
        {{ 1.f, -1.f, -1.f}, {0,   255, 0 , 0}},
        {{-1.f,  1.f, -1.f}, {0,   0,   255,0}},
        {{ 1.f,  1.f,  1.f}, {255, 255, 0,  0}},
        {{-1.f, -1.f,  1.f}, {255, 0 ,  255,0}},
        {{ 1.f, -1.f,  1.f}, {0,   255, 255,0}},
        {{-1.f,  1.f,  1.f}, {0,   0,   0,  0}},
        {{ 1.f,  1.f,  1.f}, {255, 255, 255,0}},
    };

    ID3D11Buffer* pp_VertexBuffer;
    D3D11_BUFFER_DESC bd;
    memset(&bd, 0, sizeof(bd));
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = sizeof(vertecies);
    bd.StructureByteStride = sizeof(Vertex);
    D3D11_SUBRESOURCE_DATA sd;
    memset(&sd, 0, sizeof(sd));
    sd.pSysMem = vertecies;

    const u32 stride = sizeof(Vertex);
    const u32 offset = 0u;

    // NOTE: Bind Vertex Buffer
    g->pp_Device->lpVtbl->CreateBuffer(g->pp_Device, &bd, &sd, &pp_VertexBuffer);
    g->pp_DeviceContext->lpVtbl->IASetVertexBuffers(g->pp_DeviceContext, 0u, 1u, &pp_VertexBuffer, &stride, &offset);
    // NOTE: Index buffer starts here
    
    const u16 indices[] ={
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4,
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
    g->pp_Device->lpVtbl->CreateBuffer(g->pp_Device, &ibd, &isd, &pp_IndexBuffer);
    g->pp_DeviceContext->lpVtbl->IASetIndexBuffer(g->pp_DeviceContext, pp_IndexBuffer, DXGI_FORMAT_R16_UINT, 0u);

    pp_VertexBuffer->lpVtbl->Release(pp_VertexBuffer);
  
    // NOTE: Constant buffer
    ConstantBuffer cbuffer;
    memset(&cbuffer, 0, sizeof(cbuffer));

    // WARN: Framerate dependent, the speed of the system determines rotation speed
   angle += .01f;
    if (angle >= 360.0f) {
        angle -= 360.0f;  // Keep the angle in [0, 360) range
    }
   // INFO: Transpose shifts between column and row major, at the transition
    // from the CPU to the GPU.
    //
    
    HMM_Mat4 rotationMatrix = HMM_Rotate_RH((f32)angle, (HMM_Vec3){1.0f, 0.0f, 1.0f});
    HMM_Mat4 scaleMatrix = HMM_Scale((HMM_Vec3) {1.0f, 1.0f, 1.0f});
    HMM_Mat4 transformMatrix = HMM_MulM4(rotationMatrix, scaleMatrix);
    HMM_Mat4 translationMatrix = HMM_Translate((HMM_Vec3){0.0f, 0.0f, 4.0f});
    HMM_Mat4 transformationMatrix = HMM_MulM4(translationMatrix, transformMatrix);
    HMM_Mat4 perpectiveLH = HMM_Perspective_LH_ZO(90, g->p_window->m_AspectRatio, 0.5f, 10.0f);
    cbuffer.transformation = HMM_TransposeM4(HMM_MulM4(perpectiveLH, transformationMatrix));

    ID3D11Buffer *pp_CBuffer;
    D3D11_BUFFER_DESC cbd;
    memset(&cbd, 0, sizeof(cbd));
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.ByteWidth = sizeof(cbuffer);
    cbd.StructureByteStride = 0u;
    cbd.MiscFlags = 0u;
    D3D11_SUBRESOURCE_DATA csd;
    memset(&csd, 0, sizeof(csd));
    csd.pSysMem = &cbuffer;

    g->pp_Device->lpVtbl->CreateBuffer(g->pp_Device, &cbd, &csd, &pp_CBuffer);
    g->pp_DeviceContext->lpVtbl->VSSetConstantBuffers(g->pp_DeviceContext, 0u, 1u, &pp_CBuffer);
   
    // NOTE: Pixelshader starts here
    ID3D11PixelShader* pp_PixelShader = NULL;
    ID3DBlob* pp_Blob = NULL;
    
    HRESULT hr = D3DReadFileToBlob(
        L"shaders\\pixel_shader.cso",
        &pp_Blob);

    LogError(ID3D11PixelShader, hr);
    if(FAILED(hr)) {
        SAFE_RELEASE(pp_Blob);
        return;
    }

    LogError(D3DReadFileToBlob, hr);
    hr = g->pp_Device->lpVtbl->CreatePixelShader(
        g->pp_Device,
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
    g->pp_DeviceContext->lpVtbl->PSSetShader(g->pp_DeviceContext, pp_PixelShader, NULL, 0u);

    //NOTE: Vertexshader starts here:
    ID3D11VertexShader* pp_VertexShader = NULL;

    hr = D3DReadFileToBlob(
        L"shaders\\vertex_shader.cso",
        &pp_Blob);

    LogError(D3D3ReadFileToBlob, hr);
 
    if(FAILED(hr)) {
        SAFE_RELEASE(pp_Blob);
        SAFE_RELEASE(pp_PixelShader);
        return;
    }
    
    hr = g->pp_Device->lpVtbl->CreateVertexShader(
        g->pp_Device, 
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
    g->pp_DeviceContext->lpVtbl->VSSetShader(g->pp_DeviceContext, pp_VertexShader, ((void*)0), 0u);
    
    ID3D11InputLayout* pp_InputLayout;
    const D3D11_INPUT_ELEMENT_DESC ied[] = {
        {
            "Position",
            0u,
            DXGI_FORMAT_R32G32B32_FLOAT,
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
            12u,
            D3D11_INPUT_PER_VERTEX_DATA,
            0u
        }
    };

    hr = g->pp_Device->lpVtbl->CreateInputLayout(
        g->pp_Device,
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

    g->pp_DeviceContext->lpVtbl->IASetInputLayout(g->pp_DeviceContext, pp_InputLayout);

    g->pp_DeviceContext->lpVtbl->OMSetRenderTargets(g->pp_DeviceContext, 1u, &g->pp_Target, NULL);

    g->pp_DeviceContext->lpVtbl->IASetPrimitiveTopology(g->pp_DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    D3D11_VIEWPORT vp;
    vp.Width = 800;
    vp.Height = 600;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g->pp_DeviceContext->lpVtbl->RSSetViewports(g->pp_DeviceContext,1u, &vp);
    
    //u32 vertexCount = (sizeof(vertecies) / sizeof(vertecies[0]));
    u32 indexCount = (sizeof(indices) / sizeof(indices[0]));
    g->pp_DeviceContext->lpVtbl->DrawIndexed(g->pp_DeviceContext, indexCount,0u, 0u);

    SAFE_RELEASE(pp_Blob)
    SAFE_RELEASE(pp_VertexShader);
    SAFE_RELEASE(pp_PixelShader);
    SAFE_RELEASE(pp_InputLayout);
}

void ReleaseOnAppExit(Graphics* g) {
    SAFE_RELEASE(g->pp_DeviceContext);
    SAFE_RELEASE(g->pp_SwapChain);
    SAFE_RELEASE(g->pp_Target);
    SAFE_RELEASE(g->pp_Target)
    free(g->p_window);
}
