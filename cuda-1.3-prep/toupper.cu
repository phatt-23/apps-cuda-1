#include "module.h"

// __global__ __host__ __device__

__global__ // callable from CPU
void cuda_toupper(char* str, size_t len) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    if(tid >= len || str[tid] < 'a' || str[tid] > 'z') return;

    str[tid] &= 0xdf;
    // str[tid] -= 'a' - 'A';
}

__host__ 
void cu_toupper(char* str) {
    size_t block_size = 32;
    size_t grid_size = (strlen(str) + block_size - 1) / block_size;
    
    printf("INFO: gs = %ld, bs = %ld\n\n", grid_size, block_size);
    
    cuda_toupper<<< grid_size, block_size >>>(str, strlen(str));

    cudaDeviceSynchronize();
}
