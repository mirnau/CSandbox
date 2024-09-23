#include "application.h"
#include "../window/window.h"
#include "../graphics/graphics.h"
#include <assert.h>


i32 Application_Init(Application* a) {

    a->window = calloc(1, sizeof(Window));

    Window_Run(a->window, Application_Run);

    // NOTE: Releasing the last graphics pointers.
    ReleaseOnAppExit();
    
    free(a->window);
    a->window = NULL;


    return 0; 
}

static i32 Application_Run() {

    MSG msg;

    while (TRUE)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

            if (msg.message == WM_QUIT)
            {
                return msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ClearBuffer(0.5f, 0.0f, 1.0f);
        UpdateShaders();
        Graphics_EndFrame();
        Sleep(1); // NOTE: Just testning to add it temporarly, REMOVE later?
    }
    return 0;
}
