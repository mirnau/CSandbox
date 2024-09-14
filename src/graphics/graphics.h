#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>


void Graphics_Init(HWND hwnd);
HRESULT Graphics_EndFrame();

#endif