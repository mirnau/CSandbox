#include "window.h"
#include "../math/typedef.h"
#include <stdio.h>

i64L __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    Window* window = NULL;
    switch (uMsg) {
        
        case WM_SIZE:
        window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if(window == NULL) break;
            u32 w, h, aspectRatio;
            w = (float)LOWORD(lParam);
            h = (float)HIWORD(lParam);
            if(h > 0 && w > 0) {
                window->m_AspectRatio = (float)w/h;
                printf("The value of b is: %f\n", window->m_AspectRatio);
            }

        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
