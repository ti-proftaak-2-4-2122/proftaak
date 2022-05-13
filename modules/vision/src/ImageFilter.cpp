//
// Created by tjtle on 13/05/2022.
//

#include "../include/ImageFilter.h"

void ImageFilter::add_filters(cv::Mat* img)
{
    cvtColor(*img, hsv_img, cv::COLOR_BGR2HSV_FULL);
    cv::Scalar hsv_l(100, 80, 80);
    cv::Scalar hsv_h(200, 240, 200);

    inRange(hsv_img, hsv_l , hsv_h, mask_img);
    bitwise_and(hsv_img, hsv_img, output_img, mask_img);
    //cv::resize(hsv_img, hsv_img, cv::Size(), 1000, 1000);
    cvtColor(output_img, output_img, cv::COLOR_HSV2BGR_FULL);
    cv::imshow("output", output_img);
    cv::waitKey(1);
}

void ImageFilter::filter_image()
{
    cv::VideoCapture cap(2);
    std::string path = "../resources/hsv.jpg";
    loaded_img = cv::imread(path);


    while (true)
    {
        add_filters(&loaded_img);
        cap.read(loaded_img);
        add_filters(&loaded_img);
        cv::imshow("original", loaded_img);
        cv::waitKey(1);

    }




    //cv::imshow("Image", loaded_img);


    cv::waitKey(0);

}
