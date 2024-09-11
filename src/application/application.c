#include "application.h"
#include "../window/window.h"
#include <assert.h>

i32 Application_Init(Application* a) {

    a->window = malloc(sizeof(Window));
    assert(a->window != NULL);
    
    a->window->handle = NULL;
    a->window->MessageLoop = NULL;

    a->window->MessageLoop = Application_Run;
    Window_Init(a->window);

    free(a->window);
    a->window = NULL;

    return 0; 
}

i32 Application_Run() {

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        Update();
    }

    return 0;
}

void Update() {

}