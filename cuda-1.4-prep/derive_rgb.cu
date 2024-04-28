#include "module.h"

__global__
void cuda_drive_rgb(CudaImg img) {
    uint2 tid = {
        .x = blockDim.x * blockIdx.x + threadIdx.x,
        .y = blockDim.y * blockIdx.y + threadIdx.y,
    };
    if(tid.x >= img.size.x || tid.y >= img.size.y) return;

    size_t idx = tid.y * img.size.x + tid.x;
    uchar3 tmp = img.p_uchar3[idx];

    uchar3 bgr = {
        .x = tmp.y,
        .y = tmp.z,
        .z = tmp.x,
    };

    img.p_uchar3[idx] = bgr; 
}

__host__
void cu_derive_rgb(CudaImg img, uint2 block_size) {
    dim3 grid_size(
        (img.size.x + block_size.x - 1) / block_size.x,
        (img.size.y + block_size.y - 1) / block_size.y
    );

    dim3 _block_size(
        block_size.x, 
        block_size.y  
    );

    cuda_drive_rgb<<< grid_size, _block_size >>>(img);

    cudaDeviceSynchronize();
}
