#include "inc/cu_precomp.h"
#include "inc/cu_module.h"

__global__
void cu_rotateS_img(CudaImg img, int direction) {

}

__host__
void cu_rotateS_img(CudaImg img, int direction) {
    dim3 bs(
        16, 16
    );

    dim3 gs(
        (bs.x + img.size.x - 1) / bs.x,
        (bs.y + img.size.y - 1) / bs.y
    );

    

    cudaDeviceSynchronize();
}