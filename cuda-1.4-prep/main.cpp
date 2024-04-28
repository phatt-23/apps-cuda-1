#include "module.h"


const size_t _size_y = 400;
const size_t _size_x = 500;

void img_init(cv::Mat& img) {
    for (int y = 0; y < img.rows; y++) {
        for (int x  = 0; x < img.cols; x++) {
            int dx = x - img.cols / 2;

            uchar grad = 255 * abs(dx) / (img.cols / 2);
            uchar inv_grad = 255 - grad;

            // left or right half of gradient
            uchar3 bgr = (dx < 0) ? (uchar3) { grad, inv_grad, 0 } : (uchar3) { 0, inv_grad, grad };

            // put pixel into image
            cv::Vec3b v3bgr(bgr.x, bgr.y, bgr.z);
            img.at<cv::Vec3b>(y, x) = v3bgr;
            // also possible: cv_img.at<uchar3>( y, x ) = bgr;
        }
    }
}

int main() {
    UniformAllocator allocator;
    cv::Mat::setDefaultAllocator(&allocator);

    cv::Mat cv_img(_size_y, _size_x, CV_8UC3);
    img_init(cv_img);

    CudaImg cuda_img = {
        .size = {
            .x = (uint) cv_img.size().width,
            .y = (uint) cv_img.size().height,
        },
        .p_uchar3 = (uchar3*) cv_img.data,
    };
    cv::imshow("BGR Image", cv_img);

    cu_derive_rgb(cuda_img, {16, 8});

    cv::imshow("BGR Image Inverted", cv_img);
    cv::waitKey(0);

    return 0;
}