#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>


#ifndef LogError
#define LogError(var, hr) \
    do { \
        if (FAILED(hr)) { \
            printf("%s failed with error code: 0x%08lX\n", #var, hr); \
        } \
    } while(0)

#endif

void Graphics_Init(HWND hwnd);
void UpdateShaders();
HRESULT Graphics_EndFrame();
void ClearBuffer(float r, float g, float b);
void ReleaseOnAppExit();


#endif
