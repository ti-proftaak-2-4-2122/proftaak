//
// Created by tjtle on 13/05/2022.
//

#ifndef PROFTAAK24_IMAGEFILTER_H
#define PROFTAAK24_IMAGEFILTER_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>


class ImageFilter
{
private:
    cv::Mat loaded_img;

    cv::Mat add_gaussianblur(const cv::Mat input_img);
    cv::Mat add_filter(const cv::Mat* img, const cv::Scalar& hsv_lowerbound, const cv::Scalar&
    hsv_upperbound);
    cv::Mat filter_the_blob(const cv::Mat* img);

public:
    void filter_image();

};


#endif //PROFTAAK24_IMAGEFILTER_H
