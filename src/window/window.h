#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "../math/typedef.h"

#define CLASS_NAME "Sample Window Class"
#define WINDOW_TITLE "Sample Window Title"

typedef struct {
	HWND* handle;
	i32 (*MessageLoopFunc)();
} Window;


typedef HWND WindowHandle;
i32 Window_Init(Window* window);
long long __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
i16 RegisterWindowClass(HINSTANCE hInstance);
WindowHandle CreateMainWindow(HINSTANCE hInstance);
void UnregisterWindowClass(HINSTANCE hInstance);

#endif