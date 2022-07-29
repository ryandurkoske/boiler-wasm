#pragma once

#ifdef TARGET_WASM

//MAYBE: Add more stdio.h functions

int printf(char const* format, ...);

#endif


#ifdef TARGET_NATIVE

#include <stdio.h>

#endif