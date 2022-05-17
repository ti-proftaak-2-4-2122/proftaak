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
    cv::Mat loaded_img, hsv_img, mask_img, output_img;

    void add_filters(cv::Mat* img);

    void filter_the_blob(cv::Mat* img);

public:
    void filter_image();

};


#endif //PROFTAAK24_IMAGEFILTER_H
