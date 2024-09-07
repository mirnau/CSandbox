#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <stdint.h>

#define CLASS_NAME "Sample Window Class"
#define WINDOW_TITLE "Sample Window Title"

typedef HWND WindowHandle;
int InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
int64_t __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int16_t RegisterWindowClass(HINSTANCE hInstance);
WindowHandle CreateMainWindow(HINSTANCE hInstance);
void UnregisterWindowClass(HINSTANCE hInstance);

#endif