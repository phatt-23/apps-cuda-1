#ifndef __MODULE_H
#define __MODULE_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <cuda_runtime.h>
#include <cuda_device_runtime_api.h>
#include <device_launch_parameters.h>

void cu_vec_scale(float* vec, size_t N, float scale);
void cu_vec_scaleUM(float* vec, size_t N, float scale);

#endif//__MODULE_H