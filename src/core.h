#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>

#ifndef EVALMALLOC
#define EVALMALLOC(condition) if (condition) { EvaluateMalloc(__FILE__, __LINE__); }
#endif

// Function declaration (only declaration here, no definition)
void EvaluateMalloc(const char* file, int line);

#endif // CORE_H
