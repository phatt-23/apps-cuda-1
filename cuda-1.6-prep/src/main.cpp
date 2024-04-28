#include "inc/module.h"
#include <iostream>

#if 1
int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    cv::Mat cv_img = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat cv_rot(cv_img.t().size(), CV_8UC3);

    CudaImg cuda_img(cv_img);
    CudaImg cuda_rot(cv_rot);
    
    cu_sq_rotate(cuda_img, cuda_rot, std::atoi(argv[2]));
    // cu_mirror(cuda_rot, 1);
    // cv::imshow("Rotated Image", cv_rot);
    
    // cu_mirror(cuda_rot, 0);
    // cu_mirror(cuda_rot, 1);
    cv::imshow("Mirrored Image", cv_rot);

    cv::imshow("Original Image", cv_img);

    cv::waitKey(0);
    return 0;
}
#endif

#if 0
int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    cv::Mat cv_img = cv::imread(argv[1], cv::IMREAD_COLOR);

    CudaImg cuda_img(cv_img);
    // replace with the CudaImg constructor

    cu_mirror(cuda_img, 1);

    cv::imshow("mirror", cv_img);

    cv::waitKey(0);
    return 0;
}
#endif

#if 0
int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    cv::Mat cv_img = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat cv_b(cv_img.size(), CV_8UC3);
    cv::Mat cv_g(cv_img.size(), CV_8UC3);
    cv::Mat cv_r(cv_img.size(), CV_8UC3);

    CudaImg og(cv_img);
    CudaImg b(cv_b);
    CudaImg g(cv_g);
    CudaImg r(cv_r);


    cu_split_bgr(og, b, g, r);

    cv::imshow("Original Image", cv_img);
    cv::imshow("Blue Image", cv_b);
    cv::imshow("Green Image", cv_g);
    cv::imshow("Red Image", cv_r);

    cv::waitKey(0);
    return 0;
}
#endif