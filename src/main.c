#include <Windows.h>
#include <stdint.h>
#include <stdlib.h>

#include "core.h"
#include "application/application.h"
#include "math/typedef.h"


int main(int argc, char** argv) {
    
    Application* application = malloc(sizeof(Application));

    EVALMALLOC(application == NULL);

    i32 result = Application_Init(application);

    free(application);

    return result;

}