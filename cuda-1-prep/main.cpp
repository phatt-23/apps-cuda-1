#include <stdio.h>
#include "module.h"

int main() 
{
	const size_t N = 100000000;
	float* array = nullptr;
	if(cudaMallocManaged(&array, N * sizeof(*array)) != cudaSuccess) {
		printf("Unable to allocate Unified memory!\n");
	}
	
	for(size_t i = 0; i < N; ++i) {
		array[i] = (float) i;
	}

	cu_array_mul(array, N, M_PI);
	
#if 0
	for(size_t i = 0; i < N; ++i) {
		printf("%8.2f\n", array[i]);
	}
	
#endif
	cudaFree(array);

    return 0;
}
