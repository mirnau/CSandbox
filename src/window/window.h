#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "../graphics/graphics.h"
#include "../math/typedef.h"

#define CLASS_NAME "Sample Window Class"
#define WINDOW_TITLE "Sample Window Title"

struct Window {
	HWND hWnd;
	float m_AspectRatio;
	Graphics* p_graphics;
};


Window* Window_Create();
void Window_Destroy(Window* window);
i32 Window_Run(Window* window, i32 (*func)(Graphics* p));
i64L WINAPI WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
i16 RegisterWindowClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance, Window* window);
void UnregisterWindowClass(HINSTANCE hInstance);

#endif
