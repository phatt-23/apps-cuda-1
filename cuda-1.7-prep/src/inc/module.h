#ifndef __MODULE_H
#define __MODULE_H

#include <opencv2/opencv.hpp>
#include "cu_precomp.h"
#include "uni_mem.h"
#include "cuda_img.h"

namespace cu_fn {
    enum MergeHalf {
        left_right,
        left_left,
        right_left,
        right_right,
        top_bottom,
        top_top,
        bottom_top,
        bottom_bottom,
    };

    enum Mirror {
        horizontal,
        vertical,
    };
    
};

/*
*   Breaks up the R, G, B elements from an image.
*/
void cu_split_bgr(CudaImg og, CudaImg b, CudaImg g, CudaImg r);

/*
*   Mirrors a given image, horizontaly `0` or vertically `1`.
*/
void cu_mirror(CudaImg og, cu_fn::Mirror option);

/*
*   Rotates an image into another image. 
*   @param direction -1 left rotate, 1 right rotate
*/
void cu_sq_rotate(CudaImg og, CudaImg rotated, int direction);

/*
*   Embeds an half of the `im` image into the `og`.
*/
void cu_merge_half(CudaImg og, CudaImg im, cu_fn::MergeHalf option);

#endif//__MODULE_H