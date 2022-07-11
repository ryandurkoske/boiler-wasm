#include <stdio.h>

#include "example.h"
#include "example_two.h"

int main(){
	struct example_struct eg = {4,2};
	printf("Hello World! (%d, %d)\n", eg.a, eg.b);
	printf("Hello Multiplication (%d)\n", compute_example(eg));

	struct example_two_struct eg2 = {4,2,3};
	printf("Hello World! (%d, %d)\n", eg2.a, eg2.c);
	printf("Hello Addition (%d)\n", compute_example_two(eg2));
}