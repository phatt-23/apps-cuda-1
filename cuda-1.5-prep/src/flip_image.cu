#include "inc/cu_precomp.h"
#include "inc/cu_module.h"

__global__
void cuda_flip_img(CudaImg img, size_t hv) {
    uint2 _tid = {
        .x = blockDim.x * blockIdx.x + threadIdx.x,
        .y = blockDim.y * blockIdx.y + threadIdx.y,
    };

    // return early if outside the image
    if(_tid.x >= img.size.x || _tid.y >= img.size.y) return; 

    size_t tid = _tid.y * img.size.x + _tid.x;
    size_t f_tid = 0;
    if(hv == 0)
        f_tid = ((_tid.y + 1) * img.size.x - 1) - _tid.x;
    else
        f_tid = ((img.size.y - _tid.y - 1) * img.size.x) + _tid.x;

    uchar3 tmp = img.p_uchar3[tid];
    img.p_uchar3[tid] = img.p_uchar3[f_tid];
    img.p_uchar3[f_tid] = tmp;
}

__host__
void cu_flip_img(CudaImg img, size_t hv) {
    dim3 bs(
        16,
        16
    );
    // 256 = 16**2
    dim3 gs(
        (bs.x + img.size.x - 1) / bs.x,
        (bs.y + img.size.y - 1) / bs.y
    );

    printf("block_size: %d, %d, %d\n", bs.x, bs.y, bs.z);
    printf("grid_size:  %d, %d, %d\n", gs.x, gs.y, gs.z);

    if(hv == 0) 
        gs.x = (gs.x + 1) / 2; 
    else 
        gs.y = (gs.y + 1) / 2;

    printf("grid_size:  %d, %d, %d\n", gs.x, gs.y, gs.z);

    cuda_flip_img<<<gs, bs>>>(img, hv);

    cudaDeviceSynchronize();
}
