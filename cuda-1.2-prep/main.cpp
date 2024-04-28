#include "module.h"

void vec_init(float* vec, size_t N) {
    for(size_t i = 0; i < N; ++i) {
        vec[i] = i;
    }
}

void vec_print(float* vec, size_t N) {
    printf("---------------\n");
    for(size_t i = 0; i < N; ++i) {
        printf("[%ld] =>\t%f\n", i, vec[i]);
    }
    printf("---------------\n");
}

int main() {
    const size_t N = 20;
    float* vec = nullptr;

    if( cudaMallocManaged(&vec, N * sizeof(float)) != cudaSuccess ) {
        printf("ERROR: Unable to allocate Unified memory!\n");
        exit(1);
    }

    vec_init(vec, N);
    vec_print(vec, N);
    
    cu_vec_scaleUM(vec, N, 2*M_PI);
    
    vec_print(vec, N);
    
    // float* vec = new float[N];

    // vec_init(vec, N);
    // vec_print(vec, N);

    // // cuda hovna
    // // vec * f = new_vec
    // cu_vec_scale(vec, N, M_PI);

    // vec_print(vec, N);

    // delete[] vec;

    return 0;
}