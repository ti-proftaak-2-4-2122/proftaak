//
// Created by tjtle on 13/05/2022.
//

#ifndef PROFTAAK24_IMAGEFILTER_H
#define PROFTAAK24_IMAGEFILTER_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class ImageFilter
{
private:
    cv::Mat loaded_img;

    cv::Mat add_filter(cv::Mat* img, cv::Scalar hsv_lowerbound, cv::Scalar hsv_upperbound);

public:
    void filter_image();

};


#endif //PROFTAAK24_IMAGEFILTER_H
