#ifndef REDEFINED_NUKLEAR_H
#define REDEFINED_NUKLEAR_H
/*
Nuclear fix, size of pointer is miss mached, 
fixed here, by redefining the size of the pointer
to match the expected size at compile
*/

#define NK_INCLUDE_FIXED_TYPES 
typedef size_t nk_size;  
typedef uintptr_t nk_ptr;
#include "nuklear.h"

#endif