
#ifndef APPLICATION_H
#define APPLICATION_H

#include "../window/window.h"
#include "../math/typedef.h"

typedef struct {

    Window* window;

} Application;

i32 Application_Init(Application* a);
static i32 Application_Run();

#endif
