#pragma once

#ifdef TARGET_WASM

//#define HUGE_VAL 

#define acos(x) __builtin_acos(x)
#define acosf(x) __builtin_acosf(x)

#define asin(x) __builtin_asin(x)
#define asinf(x) __builtin_asinf(x)

#define atan(x) __builtin_atan(x)
#define atanf(x) __builtin_atanf(x)

#define atan2(y,x) __builtin_atan2(y,x)
#define atan2f(y,x) __builtin_atan2f(y,x)

#define cos(x) __builtin_cos(x)
#define cosf(x) __builtin_cosf(x)

#define cosh(x) __builtin_cosh(x)
#define coshf(x) __builtin_coshf(x)

#define sin(x) __builtin_sin(x)
#define sinf(x) __builtin_sinf(x)

#define sinh(x) __builtin_sinh(x)
#define sinhf(x) __builtin_sinhf(x)

#define tan(x) __builtin_tan(x)
#define tanf(x) __builtin_tanf(x)

#define tanh(x) __builtin_tanh(x)
#define tanhf(x) __builtin_tanhf(x)

#define exp(x) __builtin_exp(x)
#define expf(x) __builtin_expf(x)

#define frexp(x, exponent) __builtin_frexp(x, exponent)
#define frexpf(x, exponent) __builtin_frexpf(x, exponent)

#define ldexp(x, exponent) __builtin_ldexp(x, exponent)
#define ldexpf(x, exponent) __builtin_ldexpf(x, exponent)

#define log(x) __builtin_log(x)
#define logf(x) __builtin_logf(x)

#define log10(x) __builtin_log10(x)
#define log10f(x) __builtin_log10f(x)

#define modf(x, integer) __builtin_modf(x, integer)
#define modff(x, integer) __builtin_modff(x, integer)

#define pow(x,y) __builtin_pow(x,y)
#define powf(x,y) __builtin_powf(x,y)

#define sqrt(x) __builtin_sqrt(x)
#define sqrtf(x) __builtin_sqrtf(x)

#define ceil(x) __builtin_ceil(x)
#define ceilf(x) __builtin_ceilf(x)

#define abs(x) __builtin_abs(x)
#define fabs(x) __builtin_fabs(x)
#define fabsf(x) __builtin_fabsf(x)

#define floor(x) __builtin_floor(x)
#define floorf(x) __builtin_floorf(x)

#define fmod(x,y) __builtin_fmod(x,y)
#define fmodf(x,y) __builtin_fmodf(x,y)

#endif
#ifdef TARGET_NATIVE

#include <math.h>

#endif