#ifndef __CUDA_IMAGE_H
#define __CUDA_IMAGE_H

#include <opencv2/core/mat.hpp>

struct CudaImg {
    uint3 size;           // size of picture
    union {
      void   *p_void;     // data of picture
      uchar1 *p_uchar1;   // data of picture
      uchar3 *p_uchar3;   // data of picture
      uchar4 *p_uchar4;   // data of picture
    };
};

#endif//__CUDA_IMAGE_H