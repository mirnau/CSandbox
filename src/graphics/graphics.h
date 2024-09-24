#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>

typedef struct Window Window;
typedef struct {
    ID3D11Device* pp_Device;
    IDXGISwapChain* pp_SwapChain;
    ID3D11DeviceContext* pp_DeviceContext;
    ID3D11RenderTargetView* pp_Target;
    Window* p_window;
} Graphics;

#ifndef LogError
#define LogError(var, hr) \
    do { \
        if (FAILED(hr)) { \
            printf("%s failed with error code: 0x%08lX\n", #var, hr); \
        } \
    } while(0)

#endif

Graphics* Graphics_Create();
void Graphics_Init(Window* window);
void UpdateShaders(Graphics* g);
HRESULT Graphics_EndFrame(Graphics* g);
void ClearBuffer(Graphics* gr, float r, float g, float b);
void ReleaseOnAppExit(Graphics* g);


#endif
