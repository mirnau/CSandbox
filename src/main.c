#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "vector.h"


int main() {

    Vector3 stack;
    Vector3 *heap = (Vector3*)malloc(sizeof(Vector3));

    heap->x = 1.0;
    heap->y = 2.0;
    heap->z = 3.0;

    printf("Hello World\n");

    vector3_print(heap);

    getchar();

    free(heap);

    return 0;
} 