#pragma once

#ifdef TARGET_WASM

#if __SIZEOF_POINTER__ == 8
    typedef  __UINT64_TYPE__ wasmpointer_t;
#elif __SIZEOF_POINTER__ == 4
    typedef  __UINT32_TYPE__ wasmpointer_t;
#endif

#define WASM_EXPORT __attribute__((visibility("default")))
#define WASM_IMPORT extern

#endif