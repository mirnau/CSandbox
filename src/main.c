#include <stdlib.h>
#include <Windows.h>
#include <stdint.h>

#include "window/window.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    UnregisterWindowClass(hInstance);

    return 0;
}

