#include <Windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "application/application.h"
#include "math/typedef.h"

#define EVALMALLOC(condition) if (condition) { EvaluateMalloc(__FILE__, __LINE__); }

void EvaluateMalloc(const char* file, int line) {
    fprintf(stderr, "Malloc Failed at %s:%d\n", file, line);
    exit(EXIT_FAILURE);
}


int main(int argc, char** argv) {
    
    Application* application = malloc(sizeof(Application));

    EVALMALLOC(application == NULL);

    i32 result = 1;

    if (Init(application)) {
       
        result = Run(application);
    }

    free(application);

    return result;

}