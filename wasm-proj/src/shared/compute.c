#include "wasm/stdlib.h"
#include "wasm/stdio.h"
#include "wasm/impexp.h"
#include <stdint.h>

#include "compute.h"

#include <stdbool.h>


#define MOD_VAL 7


WASM_EXPORT uint32_t compute_add(uint32_t* ptr, uint32_t count){
	uint32_t sum = 0;
	for(int i = 0; i < count; i++){
		sum += ptr[i];
	}

	//printf("%d primes: \n", (uint32_t)sizeof(u32x4));
	return sum;
}

WASM_EXPORT uint32_t compute_add_unrolled(uint32_t* ptr, uint32_t count){
	uint32_t sum = 0;
	for(int i = 0; i < count/4; i++){
		sum += ptr[4*i]+ptr[4*i+1]+ptr[4*i+2]+ptr[4*i+3];
	}
	uint32_t rem = count%4;
	for(int i = count-rem; i < count; i++){
		sum += ptr[i];
	}

	//printf("%d primes: \n", (uint32_t)sizeof(u32x4));
	return sum;
}

WASM_EXPORT uint32_t compute_branch(uint32_t* ptr, uint32_t count){
	uint32_t sum = 0;
	for(int i = 0; __builtin_expect(i < count, true); i++){
		sum++;
		if(ptr[i]%MOD_VAL==0){//no reason, just want it to be hard to branchless optimize
			sum%=17;
		}
	}

	//printf("%d primes: \n", (uint32_t)sizeof(u32x4));
	return sum;
}

WASM_EXPORT uint32_t compute_branch_predict(uint32_t* ptr, uint32_t count){
	uint32_t sum = 0;
	for(int i = 0; i < count; i++){
		sum++;
		if(__builtin_expect(ptr[i]%MOD_VAL==0,false)){//no reason, just want it to be hard to branchless optimize
			sum%=17;
		}
	}

	//printf("%d primes: \n", (uint32_t)sizeof(u32x4));
	return sum;
}

WASM_EXPORT uint32_t compute_branchless(uint32_t* ptr, uint32_t count){
	uint32_t sum = 0;
	for(int i = 0; i < count; i++){
		sum++;
		//sum = ptr[i]%MOD_VAL==0 ? sum%17 : sum;
		if(__builtin_unpredictable(ptr[i]%MOD_VAL==0)){//no reason, just want it to be hard to branchless optimize
			sum%=17;
		}
	}

	return sum;
}