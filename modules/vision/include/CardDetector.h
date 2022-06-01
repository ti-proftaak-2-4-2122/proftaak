//
// Created by tjtle on 13/05/2022.
//
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>


class CardDetector
{

protected:
    struct Card
    {
        unsigned int color;
        double x;
        double y;
    };



private:
    CardDetector()
    = default;

    inline zstatic CardDetector* singleton_;

    cv::Mat loaded_img;
    bool initialized = false;

    //colours
    struct ColorFilter
    {
        unsigned int color;
        cv::Scalar low;
        cv::Scalar high;
    };
    const ColorFilter green = ColorFilter{0, cv::Scalar(80, 50, 50), cv::Scalar(120, 220, 220)};
    const ColorFilter red = ColorFilter{1, cv::Scalar(245, 190, 100), cv::Scalar(255, 230, 200)};
    const ColorFilter red2 = ColorFilter{1, cv::Scalar(0, 190, 100), cv::Scalar(15, 230, 200)};
    const ColorFilter yellow = ColorFilter{2, cv::Scalar(30, 80, 80), cv::Scalar(60, 245, 245)};

    const std::vector<ColorFilter> colours = {yellow, red, green};

    std::vector<Card> cards;

    void Initialize();

    static cv::Mat GetBlurredImage(const cv::Mat& input_img);

    static cv::Mat GetFilteredImage(const cv::Mat *img, const ColorFilter &color);

    cv::Mat FilterTheBlob(const cv::Mat *img, const ColorFilter& color);

    static void PrintCard(Card card);

    static cv::Scalar GetColor(unsigned int colorCode);

public:
    /**
 * Static methods should be defined outside the class.
 */
    static CardDetector *GetInstance()
    {
        /**
         * This is a safer way to create an instance. instance = new Singleton is
         * dangeruous in case two instance threads wants to access at the same time
         */
        if(singleton_==nullptr){
            singleton_ = new CardDetector();
        }
        return singleton_;
    }

    cv::Mat UpdateCards(const cv::Mat &input_image);

    std::vector<Card> GetDetectedCards();

    void PrintCards();
};