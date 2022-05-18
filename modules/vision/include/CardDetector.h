//
// Created by tjtle on 13/05/2022.
//

#ifndef PROFTAAK24_CARDDETECTOR_H
#define PROFTAAK24_CARDDETECTOR_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>


class CardDetector
{
protected:
    struct Card {
        unsigned int color;
        double x;
        double y;
    };

private:
    cv::Mat loaded_img;
    bool initialized = false;

    //colours
    struct ColorFilter {
        unsigned int color;
        cv::Scalar high;
        cv::Scalar low;
    };

    const ColorFilter green = ColorFilter{0, cv::Scalar(80, 100, 100), cv::Scalar(120, 200,200)};
//    const ColorFilter red = ColorFilter{0, cv::Scalar(80, 100, 100), cv::Scalar(120, 200,200)};
    const ColorFilter yellow = ColorFilter{0, cv::Scalar(25, 100, 100), cv::Scalar(55, 200, 200)};

    const std::vector<ColorFilter> colours = {green, yellow};
    std::vector<Card> cards;

    void Initialize();
    cv::Mat GetBlurredImage(const cv::Mat input_img);
    cv::Mat GetFilteredImage(const cv::Mat* img, const ColorFilter color);
    cv::Mat FilterTheBlob(const cv::Mat* img, const ColorFilter color);

public:
    void UpdateCards(const cv::Mat& input_image);
    std::vector<Card> GetDetectedCards();

};


#endif //PROFTAAK24_CARDDETECTOR_H
