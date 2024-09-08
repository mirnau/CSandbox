#include "window.h"

int InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    
    if (!RegisterWindowClass(hInstance)) {
        return 0;
    }

    HWND hwnd = CreateMainWindow(hInstance);
    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hwnd);

    MSG msg;
    
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterWindowClass(hInstance);

    return 0;

}

int16_t RegisterWindowClass(HINSTANCE hInstance) {
    WNDCLASS wc = {0};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    return RegisterClass(&wc);
}

WindowHandle CreateMainWindow(HINSTANCE hInstance) {
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