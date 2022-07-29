#include "example.h"
#include "example_two.h"

#include <stdint.h>
#include <wasm_simd128.h>
#include "wasm/stdlib.h"
#include "wasm/stdio.h"
#include "wasm/impexp.h"

/*
#include <float.h>

#include <iso646.h>
#include <limits.h>


#include <stdalign.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>

#include <stdbool.h>


#include <stdnoreturn.h>*/

#include "wasm/math.h"
#include "wasm/assert.h"

static_assert(sizeof(char)==1,"char wrong size");
static_assert(sizeof(short)==2,"short wrong size");
static_assert(sizeof(int)==4,"int wrong size");
static_assert(sizeof(long long int)==8,"long long int wrong size");

WASM_EXPORT void hello_wasm(){

	struct example_struct eg = {21,2};
	printf("Hello World! (%d, %d)\n", eg.a, eg.b);
	printf("Hello %s (%d)\n", "Multiplication", compute_example(eg));

	struct example_two_struct eg2 = {31,7,4};
	printf("Hello World! (%d, %d, %d)\n", eg2.a, eg2.b, eg2.c);
	printf("Hello %s (%d)\n", "Addition", compute_example_two(eg2));

	//__builtin_wasm_throw(7, &eg2);


	int val = 42;
	printf("sqrtf(%d)=%.8f\n", val, sqrtf((float)val));
	printf("sqrt(%d)=%.17lf\n", val, sqrt((double)val));
	
}

WASM_EXPORT uint32_t compute_add_vec(uint32_t* ptr, uint32_t count){

	uint32_t sum = 0;
	__u32x4* vec_ptr = (__u32x4*)ptr;
	__u32x4 vec_sum = {0,0,0,0};

	for(int i = 0; i < count/4; i++){
		vec_sum += vec_ptr[i];
	}
	uint32_t rem = count%4;
	for(int i = count-rem; i < count; i++){
		sum += ptr[i];
	}
	uint32_t upper = vec_sum[0]+vec_sum[1];
	uint32_t lower = vec_sum[2]+vec_sum[3];
	sum += upper+lower;

	

	//printf("%d primes: \n", (uint32_t)sizeof(u32x4));
	

	return sum;
}