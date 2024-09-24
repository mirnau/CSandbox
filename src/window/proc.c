#include "window.h"
#include "../math/typedef.h"

i64L __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

        Window* window = NULL;

        case WM_CREATE:
            
        window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            window->m_AspectRatio = 0.75f;
            break;
        
        case WM_SIZE:
        window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            u32 w, h, aspectRatio;
            w = (float)LOWORD(lParam);
            h = (float)HIWORD(lParam);
            if(h > 0 && w > 0) window->m_AspectRatio = (float)w/h;
            
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
