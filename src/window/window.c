#include "window.h"
#include "../graphics/graphics.h"


Window* Window_Create() {
    Window* w = calloc(1, sizeof(Window));
    w->p_graphics = Graphics_Create();
    w->p_graphics->p_window = w;
    w->m_AspectRatio = 1.f;
    return w;
}
void Window_Destroy(Window* w) {
    free(w->hWnd);
    ReleaseOnAppExit(w->p_graphics);
    free(w);
}

i32 Window_Run(Window* w, i32 (*RunMessageLoop)(Graphics* g)) {
    
    HINSTANCE hInstance = GetModuleHandle(NULL);
    LPSTR lpCmdLine = GetCommandLine();
    int nCmdShow = SW_SHOWDEFAULT;

    if (!RegisterWindowClass(hInstance)) {
        return 0;
    }

    w->hWnd = CreateMainWindow(hInstance, w);
    if (w->hWnd == NULL) {
        return 0;
    }
    SetWindowLongPtr(w->hWnd, GWLP_USERDATA, (LONG_PTR) w);

    Graphics_Init(w);
    ShowWindow(w->hWnd, SW_SHOWMAXIMIZED);
    UpdateWindow(w->hWnd);

    i32 result = RunMessageLoop(w->p_graphics);

    UnregisterWindowClass(hInstance);

    return result;

}

i16 RegisterWindowClass(HINSTANCE hInstance) {
    WNDCLASS wc = {0};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    return RegisterClass(&wc);
}

HWND CreateMainWindow(HINSTANCE hInstance, Window* window) {
    return CreateWindowEx(
        0,                      // Optional window styles
        CLASS_NAME,             // Window class name
        WINDOW_TITLE,           // Window text at the top
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,    // Window style
        CW_USEDEFAULT,          // Position x
        CW_USEDEFAULT,          // Position y
        CW_USEDEFAULT,          // Width
        CW_USEDEFAULT,          // Height
        NULL,                   // Parent window    
        NULL,                   // Menu
        hInstance,              // Instance handle
        NULL                    // Additional application data
    );
}

void UnregisterWindowClass(HINSTANCE hInstance) {
    UnregisterClass(CLASS_NAME, hInstance);
}
