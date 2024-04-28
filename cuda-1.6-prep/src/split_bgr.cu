#include "inc/cu_precomp.h"
#include "inc/cuda_img.h"

__global__
void cuda_split_bgr(CudaImg og, CudaImg b, CudaImg g, CudaImg r) {
    uint2 pos = {
        .x = blockDim.x * blockIdx.x + threadIdx.x,
        .y = blockDim.y * blockIdx.y + threadIdx.y,
    };
    
    if(pos.x >= og.size.x) return;
    if(pos.y >= og.size.y) return;

    uint tid = pos.y * og.size.x + pos.x;

    uchar3 color = og.p_uchar3[tid];

    b.p_uchar3[tid].x = color.x;
    g.p_uchar3[tid].y = color.y;
    r.p_uchar3[tid].z = color.z;
}

__host__
void cu_split_bgr(CudaImg og, CudaImg b, CudaImg g, CudaImg r) {
    dim3 block_dim(
        16, 16, 1
    );
    dim3 grid_dim(
        (og.size.x + block_dim.x - 1) / block_dim.x,
        (og.size.y + block_dim.y - 1) / block_dim.y,
        1
    );

    cuda_split_bgr<<<grid_dim, block_dim>>>(og, b, g, r);

    cudaDeviceSynchronize();
}


__global__
void cuda_mirror(CudaImg og, uint8_t hor_vert) {
    uint2 pos = {
        .x = blockDim.x * blockIdx.x + threadIdx.x,
        .y = blockDim.y * blockIdx.y + threadIdx.y
    };

    uint tid = pos.y * og.size.x + pos.x;

    // hor
    uint mirror_tid;
    if (!hor_vert)
        mirror_tid = tid + og.size.x - 2 * pos.x - 1;
    else
        mirror_tid = (pos.y + og.size.y - 2 * pos.y) * og.size.x + pos.x - og.size.x;
    
    uchar3 temp = og.p_uchar3[tid];
    og.p_uchar3[tid] = og.p_uchar3[mirror_tid];
    og.p_uchar3[mirror_tid] = temp;
}

__host__
void cu_mirror(CudaImg og, uint8_t hor_vert) {
    dim3 bd;
    // 1024 = 2^10
    for(size_t i = 10; i > 0; i--) {
        bd.x = 1 << i;
        if((og.size.x / bd.x) % 2 == 0 && (og.size.x % bd.x) == 0) {
            break;
        }
    }

    for(size_t i = 10; i > 0; i--) {
        bd.y = 1 << i;
        if((og.size. y/ bd.y) % 2 == 0 && (og.size.y % bd.y) == 0) {
            break;
        }
    }
    printf("block_dim: x = %d, y = %d, z = %d\n", bd.x, bd.y, bd.z);

    // 0 = hor
    // 1 = vert
    
    dim3 gd(
        (og.size.x + bd.x - 1) / bd.x,
        (og.size.y + bd.y - 1) / bd.y,
        1
    );
    
    if (!hor_vert) {
        gd.x /= 2;
    } else {
        gd.y /= 2;
    }

    cuda_mirror<<< gd, bd >>>(og, hor_vert);
    
    cudaDeviceSynchronize();
}