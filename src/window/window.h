#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <stdint.h>

#define CLASS_NAME "Sample Window Class"
#define WINDOW_TITLE "Sample Window Title"

typedef struct {
	HWND* handle;
} Window;


typedef HWND WindowHandle;
int InitWindow();
int64_t __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int16_t RegisterWindowClass(HINSTANCE hInstance);
WindowHandle CreateMainWindow(HINSTANCE hInstance);
void UnregisterWindowClass(HINSTANCE hInstance);

#endif