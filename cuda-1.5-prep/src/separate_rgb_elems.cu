#include "inc/cu_module.h"

__global__
void cuda_separate_rgb_elems(CudaImg og, CudaImg b, CudaImg g, CudaImg r) {
    uint2 _tid = {
        .x = blockDim.x * blockIdx.x + threadIdx.x,
        .y = blockDim.y * blockIdx.y + threadIdx.y,
    };

    if(og.size.y <= _tid.y) return;
    if(og.size.x <= _tid.x) return;

    size_t tid = _tid.y * og.size.x + _tid.x;
    uchar3 color = og.p_uchar3[tid];

    b.p_uchar3[tid].x = color.x;
    g.p_uchar3[tid].y = color.y;
    r.p_uchar3[tid].z = color.z;
}

__host__
void cu_separate_rgb_elems(CudaImg og, CudaImg b, CudaImg g, CudaImg r) {
    dim3 block_size( 16, 16 );
    dim3 grid_size( 
        (block_size.x + og.size.x - 1) / block_size.x,
        (block_size.y + og.size.y - 1) / block_size.y
    );

    cuda_separate_rgb_elems<<<grid_size, block_size>>>(og, b, g, r);

    cudaDeviceSynchronize();
}

