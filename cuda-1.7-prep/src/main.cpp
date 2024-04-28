#include "inc/module.h"
#include <iostream>

#if 0
int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    cv::Mat cv_img = cv::imread(argv[1], cv::IMREAD_COLOR);
    CudaImg cuda_img(cv_img);

    cv::imshow("Original Image", cv_img);



    cv::imshow("Scaled Image", cv_img);

    cv::waitKey(0);
    return 0;
}
#endif

#if 1
int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    cv::Mat cv_img1 = cv::imread(argv[1], cv::IMREAD_UNCHANGED);
    cv::Mat cv_img2 = cv::imread(argv[2], cv::IMREAD_UNCHANGED);

    CudaImg cuda_img1(cv_img1);
    CudaImg cuda_img2(cv_img2);
    
    cv::imshow("Original Image 1", cv_img1);
    cv::imshow("Original Image 2", cv_img2);

    cu_insert_per(
        cuda_img1, 
        cuda_img2, 
        std::atoi(argv[3]), 
        (cu_fn::Position) std::atoi(argv[4])
    );
    // cu_merge_half(cuda_img1, cuda_img2, (cu_fn::MergeHalf) std::atoi(argv[3]));

    cv::imshow("Image 2 inseted into Image 1", cv_img1);

    cv::waitKey(0);
    return 0;
}
#endif
