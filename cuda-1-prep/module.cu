#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <driver_types.h>
#include <stdio.h>

__global__ void thread_hierarchy() {
    int l_x = threadIdx.x + blockIdx.x * blockDim.x;
    int l_y = threadIdx.y + blockIdx.y * blockDim.y;
    printf("Block{%d,%d}[%d,%d] Thread{%d,%d}[%d,%d] [%d,%d]\n",
        gridDim.x, gridDim.y, blockIdx.x, blockIdx.y,
        blockDim.x, blockDim.y, threadIdx.x, threadIdx.y, l_x, l_y);
}

void cu_run_cuda(dim3 t_grid_size, dim3 t_block_size) {
    cudaError_t l_cerr;
    
    thread_hierarchy<<< t_grid_size, t_block_size >>>();
    
    if((l_cerr = cudaGetLastError()) != cudaSuccess)
        printf("CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString(l_cerr));

    cudaDeviceSynchronize();
}

__global__ void cuda_array_mul(float* array, size_t len, float factor)
{
	size_t i = blockDim.x * blockIdx.x + threadIdx.x;
	if(i >= len) return;
	array[i] *= factor;
}

void cu_array_mul(float* array, size_t len, float factor)
{
	cudaError_t err;
	int threads = 128;
	int blocks = (threads + len - 1) / threads;
	cuda_array_mul<<< blocks, threads >>>(array, len, factor);

	if((err = cudaGetLastError()) != cudaSuccess) {
		printf("ERROR: [%d] '%s'\n", __LINE__, cudaGetErrorString(err));
	}

	cudaDeviceSynchronize();
}

