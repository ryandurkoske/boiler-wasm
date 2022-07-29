#pragma once


#ifdef TARGET_WASM

typedef __SIZE_TYPE__ size_t;
void* malloc(size_t);

#endif
#ifdef TARGET_NATIVE

#include <stdlib.h>

#endif