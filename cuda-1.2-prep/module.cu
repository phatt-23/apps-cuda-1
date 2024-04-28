#include "module.h"

// qualifier <= kernel fn, runs on GPU 
__global__ 
void cuda_vec_scale(float* vec, size_t N, float scale) {
    // rule 1) No conditional jumps - i.e. if {} else {}, for {}, while {}
    
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if(tid >= N) return; 

    vec[tid] *= scale;
}

// interface function <= runs on CPU
void cu_vec_scale(float* vec, size_t N, float scale) {
    // 1. allocate GPU memory
    float* cu_vec = nullptr;

    cudaMalloc(&cu_vec, N * sizeof(float));
    
    // 2. copy from CPU to GPU memory
    cudaMemcpy(cu_vec, vec, N * sizeof(float), cudaMemcpyHostToDevice);

    // 3. calculate grid_size and block_size
    // * * * | * * *  
    // * * * | * * *  
    // * * * | * * * 
    // ------+-------
    // * * * | * * *  
    // * * * | * * *  
    // * * * | * * *  
    
    // vec[500], n = 500

    size_t block_size = 128; // count of threads in one block
    size_t grid_size = (N + block_size - 1) / block_size; // count of blocks in a grid


    printf("N = %ld, scale = %f, grid_size = %ld, block_size = %ld\n", 
        N, scale, grid_size, block_size);

    // 4. call kernel
    // fn<<< grid_size, block_size >>>(...)
    cuda_vec_scale<<< grid_size, block_size >>>(cu_vec, N, scale);

    // 5. copy back data from GPU to CPU 
    cudaMemcpy(vec, cu_vec, N * sizeof(float), cudaMemcpyDeviceToHost);

    cudaFree(cu_vec);
}

void cu_vec_scaleUM(float* vec, size_t N, float scale) {
    size_t block_size = 128; 
    size_t grid_size = (N + block_size - 1) / block_size; 

    cuda_vec_scale<<< grid_size, block_size >>>(vec, N, scale);
    
    cudaDeviceSynchronize();
    
    return;
}