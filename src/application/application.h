
#ifndef APPLICATION_H
#define APPLICATION_H

#include "../window/window.h"
#include "../math/typedef.h"

typedef struct {

    Window* window;

} Application;

i32 Application_Init(Application* a);
i32 Application_Run();
void Update();

#endif