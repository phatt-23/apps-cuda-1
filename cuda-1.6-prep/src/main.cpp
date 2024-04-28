#include "inc/module.h"
#include <iostream>

int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    cv::Mat cv_img = cv::imread(argv[1], cv::IMREAD_COLOR);

    CudaImg cuda_img = {
        .size = {
            .x = cv_img.size().width,
            .y = cv_img.size().height,
        },
        .p_uchar3 = (uchar3*) cv_img.data
    };

    cu_mirror(cuda_img, 1);

    cv::imshow("mirror", cv_img);

    cv::waitKey(0);
    

    return 0;
}

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