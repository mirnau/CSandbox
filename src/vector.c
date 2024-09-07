#include "vector.h"
#include <stdio.h>

void vector3_print(const Vector3 *v) {
        printf("Vector: (%.2f, %.2f, %.2f)\n", v->x, v->y, v->z);    
}
