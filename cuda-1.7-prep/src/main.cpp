#include "inc/module.h"
#include <iostream>

int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    cv::Mat cv_img1 = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat cv_img2 = cv::imread(argv[2], cv::IMREAD_COLOR);

    CudaImg cuda_img1(cv_img1);
    CudaImg cuda_img2(cv_img2);
    
    cv::imshow("Original Image 1", cv_img1);
    cv::imshow("Original Image 2", cv_img2);

    cu_merge_half(cuda_img1, cuda_img2, (cu_fn::MergeHalf) std::atoi(argv[3]));

    cv::imshow("Image 1 merged with Image 2", cv_img1);

    cv::waitKey(0);
    return 0;
}

