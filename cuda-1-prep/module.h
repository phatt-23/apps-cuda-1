#ifndef __MODULE_H
#define __MODULE_H

#include <cuda_runtime.h>
#include <cuda_device_runtime_api.h>
#include <math.h>

// cuda 1
void cu_run_cuda(dim3 gs, dim3 bs);

// cuda 2
void cu_array_mul(float* array, size_t len, float factor);



#endif//__MODULE_H
