#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef unsigned char u8;
typedef unsigned  short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64; // long could be either 32 or 64 bits, depending on your platform and compiler
typedef long long i64L; // long long is 64 bits, which is standard for most systems.
typedef float f32;
typedef double f64;

typedef struct { f32 x,  y; } Vector2;

#endif 