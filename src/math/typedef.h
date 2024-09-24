#include "../../vendor/libs/HandmadeMath/HandmadeMath.h"

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

//typedef HMM_Vec2 Vector2;
typedef HMM_Vec3 Vector3;
typedef HMM_Quat Quaternion;



typedef struct { 
    
    Vector3 pos;
    struct {
        u8 r; 
        u8 g; 
        u8 b;
        u8 a;
    } color;
} Vertex;

/* NOTE: The constant buffer implementaiton computes
** using SIMD, which is performance optimized compared
** to regular c-style matrix multiplicaiton.
*/ 
typedef struct {
    HMM_Mat4 transformation;
} ConstantBuffer;

#endif 
