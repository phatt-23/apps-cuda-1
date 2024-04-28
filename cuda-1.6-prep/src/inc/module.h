#ifndef __MODULE_H
#define __MODULE_H

#include <opencv2/opencv.hpp>
#include "cu_precomp.h"
#include "uni_mem.h"
#include "cuda_img.h"

void cu_split_bgr(CudaImg og, CudaImg b, CudaImg g, CudaImg r);
void cu_mirror(CudaImg og, uint8_t hor_vert);

#endif//__MODULE_H