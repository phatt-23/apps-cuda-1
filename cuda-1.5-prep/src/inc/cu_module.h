#ifndef __MODULE_H
#define __MODULE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "uni_mem.h"
#include "cuda_img.h"

/*
* Separates the `og` image to 3 images holding only `r`, `g` and `b` values. 
*/
void cu_separate_rgb_elems(CudaImg og, CudaImg b, CudaImg g, CudaImg r);

/*
* Flips an image horizontally or vertically.
* @param hv - if 0 then the image flips horizontally, 1 if vertically
*/
void cu_flip_img(CudaImg img, size_t hv);

/*
* Rotates an CudaImg `img` by `degrees`.
* @param degrees - in degrees, not radians
*/
void cu_rotate_img(CudaImg img, float degrees);

/*
* Rotates an image by 90° in a `direction`.
* @param direction can be [-2, -1, 1, 2]
*/
void cu_rotateS_img(CudaImg img, int direction);

#endif//__MODULE_H