#include "example.h"
#include "example_two.h"

#include <stdint.h>
#include "wasm/impexp.h"
#include "wasm/io.h"

WASM_EXPORT void hello_wasm(){
	struct example_struct eg = {21,2};
	printf("Hello World! (%d, %d)\n", eg.a, eg.b);
	printf("Hello Multiplication (%d)\n", compute_example(eg));

	struct example_two_struct eg2 = {31,7,4};
	printf("Hello World! (%d, %d, %d)\n", eg2.a, eg2.b, eg2.c);
	printf("Hello Addition (%d)\n", compute_example_two(eg2));
}

WASM_EXPORT uint32_t compute_add(uint32_t* ptr, uint32_t count){
	uint32_t sum = 0;
	for(int i = 0; i < count; i++){
		printf("hello: %d\n", ptr[i]);
		sum += ptr[i];
	}
	return sum;
}