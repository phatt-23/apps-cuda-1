#ifndef __MODULE_H
#define __MODULE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cuda_device_runtime_api.h>
#include <device_launch_parameters.h>
#include "uni_mem_allocator.h"
#include "cuda_image.h"

void cu_derive_rgb(CudaImg img, uint2 block_size);

#endif//__MODULE_H