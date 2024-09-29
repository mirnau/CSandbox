#include "application.h"
#include "../window/window.h"
#include "../graphics/graphics.h"
#include <assert.h>


i32 Application_Init(Application* a) {

    a->window = Window_Create();

    assert(a->window != NULL);

    Window_Run(a->window, Application_Run);

    Window_Destroy(a->window);
   
    a->window = NULL;

    return 0; 
}

static i32 Application_Run(Graphics* g) {

    MSG msg;

    while(TRUE)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

            if (msg.message == WM_QUIT)
            {
                return msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ClearBuffer(g, 0.5f, 0.0f, 1.0f);
        UpdateShaders(g);
        Graphics_EndFrame(g);
        Sleep(1); // NOTE: Just testning to add it temporarly, REMOVE later?
    }
    return 0;
}
