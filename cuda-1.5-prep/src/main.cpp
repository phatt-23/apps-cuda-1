#include "inc/cu_module.h"

int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    if(argc < 2) {
        printf("Enter a filepath of an image to flip!\n");
        exit(-1);
    }

    cv::Mat cv_img = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::imshow("Origiral Image", cv_img);

    cu_rotateS_img(cv_img, std::atoi(argv[2]));

    cv::imshow("Flipped Image", cv_img);
    cv::waitKey(0);
    return 0;
}

#if 0
int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    if(argc < 2) {
        printf("Enter a filepath of an image to flip!\n");
        exit(-1);
    }

    cv::Mat cv_img = cv::imread(argv[1], cv::IMREAD_COLOR);

    cv::imshow("Origiral Image", cv_img);

    cu_flip_img(cv_img, std::atoi(argv[2]));

    cv::imshow("Flipped Image", cv_img);

    cv::waitKey(0);
    return 0;
}
#endif

#if 0
int main(int argc, char** argv) {
    UniformAllocator allc;
    cv::Mat::setDefaultAllocator(&allc);

    if(argc < 2) {
        printf("Enter picture filepath!\n");
        exit(-1);
    }

    cv::Mat cv_bgr_img = cv::imread(argv[1], cv::IMREAD_COLOR);

    if(!cv_bgr_img.data) {
        printf("Failed to read in the file %s\n", argv[1]);
        exit(-1);
    }

    cv::Mat cv_b_img(cv_bgr_img.size(), CV_8UC3);
    cv::Mat cv_g_img(cv_bgr_img.size(), CV_8UC3);
    cv::Mat cv_r_img(cv_bgr_img.size(), CV_8UC3);

    CudaImg cu_bgr_img(cv_bgr_img);
    CudaImg cu_b_img(cv_b_img);
    CudaImg cu_g_img(cv_g_img);
    CudaImg cu_r_img(cv_r_img);
    
    cu_separate_rgb_elems(cu_bgr_img, cu_b_img, cu_g_img, cu_r_img);

    cv::imshow("Original Image", cv_bgr_img);
    cv::imshow("Blue Image", cv_b_img);
    cv::imshow("Green Image", cv_g_img);
    cv::imshow("Red Image", cv_r_img);

    cv::waitKey(0);
    return 0;
}
#endif