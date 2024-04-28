#include "inc/cuda_img.h"

CudaImg::CudaImg(cv::Mat& img) {
    size.x = img.size().width;
    size.y = img.size().height;
    p_void = (void*) img.data;
}

// __device__ uchar3& CudaImg::at3(int x, int y) {
//     return this->p_uchar3[y * this->size.x + x];
// }

