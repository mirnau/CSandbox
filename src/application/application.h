
#ifndef APPLICATION_H
#define APPLICATION_H

#include "../math/typedef.h"
#include "../window/window.h"

typedef struct {

    Window* window;

} Application;

i32 Application_Init(Application* a);
static i32 Application_Run(Graphics* g);

#endif
