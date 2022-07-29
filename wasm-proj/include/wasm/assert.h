#pragma once


#ifdef TARGET_WASM

#define static_assert(bool,msg) _Static_assert(bool,msg)

#endif
#ifdef TARGET_NATIVE

#include <assert.h>

#endif