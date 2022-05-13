//
// Created by tjtle on 13/05/2022.
//

#include "../include/ImageFilter.h"

void ImageFilter::add_filters(cv::Mat* img)
{
    cvtColor(*img, hsv_img, cv::COLOR_BGR2HSV_FULL);
    cv::Scalar hsv_l(0, 0, 0);
    cv::Scalar hsv_h(255, 255, 255);

    inRange(hsv_img, hsv_l , hsv_h, mask_img);
    bitwise_and(hsv_img, hsv_img, output_img, mask_img);
    //cv::resize(hsv_img, hsv_img, cv::Size(), 1000, 1000);
    imshow("output", hsv_img);

}

void ImageFilter::filter_image()
{

    std::string path = "../resources/hsv.jpg";
    loaded_img = cv::imread(path);

    add_filters(&loaded_img);




    //cv::imshow("Image", loaded_img);


    cv::waitKey(0);

}
