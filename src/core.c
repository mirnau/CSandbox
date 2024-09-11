#include "core.h"

void EvaluateMalloc(const char* file, int line) {
    fprintf(stderr, "Malloc Failed at %s:%d\n", file, line);
    exit(EXIT_FAILURE);
}