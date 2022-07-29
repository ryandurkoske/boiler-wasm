#include <stdio.h>
#include <windows.h>

#include "compute.h"
#include "example.h"
#include "example_two.h"

#include "wasm/assert.h"

double pc_freq;
uint64_t pc_counter;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    	printf("QueryPerformanceFrequency failed!\n");

    pc_freq = ((double)li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    pc_counter = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return ((double)(li.QuadPart-pc_counter))/pc_freq;
}

int main(){
	struct example_struct eg = {4,2};
	printf("Hello World! (%d, %d)\n", eg.a, eg.b);
	printf("Hello Multiplication (%d)\n", compute_example(eg));

	struct example_two_struct eg2 = {4,2,3};
	printf("Hello World! (%d, %d)\n", eg2.a, eg2.c);
	printf("Hello Addition (%d)\n", compute_example_two(eg2));



	int32_t res;
	double dt;

	int32_t prime_count = 100000;
	
	StartCounter();
	res = compute_branch(&primes[0], prime_count);
	dt = GetCounter();

	printf("The first %d primes sum up to %d\n", prime_count, res);
	printf("Took: %.5fms\n", dt);

}