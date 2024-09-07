#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  double x;
  double y; 
  double z;
} Vector3;

void vector3_print(const Vector3 *v);

#endif