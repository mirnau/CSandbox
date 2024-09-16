#include "application.h"
#include "../window/window.h"
#include "../graphics/graphics.h"
#include <assert.h>
#include "../../include/redefined_nuklear.h"

NK_API struct nk_context ctx;

i32 Application_Init(Application* a) {

    a->window = calloc(1, sizeof(Window));

    Window_Init(a->window, Application_Run);

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
        Graphics_EndFrame();
        Update();
    }
}

    return 0;
}

void Update() {
    
}