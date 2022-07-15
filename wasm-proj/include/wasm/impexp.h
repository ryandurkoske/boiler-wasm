#pragma once

#ifdef TARGET_WASM

#define WASM_EXPORT __attribute__((visibility("default")))
#define WASM_IMPORT extern

#endif

#ifdef TARGET_NATIVE

#define WASM_EXPORT
#define WASM_IMPORT

#endif

