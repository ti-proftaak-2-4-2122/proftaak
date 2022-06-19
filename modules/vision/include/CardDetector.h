/**
 * @file
 * @brief Header file for the CardDetector class
 * @author tjtle
 * @date 13-05-2022
 */
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include "UnitTypeEnum.h"

/**
 * @class CardDetector filters the card based on 3 colour filters:
 * a @red filter,
 * a @green filter
 * and a @yellow filter
 * These filters are used to divide the detected objects into sub classifications
 * And then used to further identify data within the cards, such as location and colour of the card.
 */
class CardDetector
{
public:
    struct Card
    {
        unsigned int color;
        double x;
        double y;
        bool isUsed;
    };

    /**
    * Static methods should be defined outside the class.
    */
    static CardDetector *GetInstance()
    {
        /**
         * This is a safer way to create an instance. instance = new Singleton is
         * dangerous in case two instance threads wants to access at the same time
         */
        if(singleton_==nullptr){
            singleton_ = new CardDetector();
        }
        return singleton_;
    }

    /**
     * @brief Uses the function @FilterTheBlob to update the list of detected @cards
     * @param input_image is the filtered img, most likely Gauss Filtered
     * @return the detected card to use it in @Spawner
     */
    cv::Mat UpdateCards(const cv::Mat &input_image);

    std::vector<Card> GetDetectedCards();

    /**
     * @brief Print function to print every card's dataset
     */
    void PrintCards();

private:
    CardDetector() = default;

    inline static CardDetector* singleton_;

    cv::Mat loaded_img;
    bool initialized = false;

    std::mutex cardsUpdateLock; //Mutex to prevent resource sharing to become chaotic

    //Filter of the colour that needs to be extracted
    struct ColorFilter
    {
        unsigned int color;
        cv::Scalar low;
        cv::Scalar high;
    };

    /**
     * @brief Predefined colour filters
     */
    const ColorFilter green = ColorFilter{0, cv::Scalar(80, 50, 50), cv::Scalar(120, 220, 220)};
    const ColorFilter red = ColorFilter{1, cv::Scalar(245, 190, 100), cv::Scalar(255, 230, 200)};
    const ColorFilter red2 = ColorFilter{1, cv::Scalar(0, 190, 100), cv::Scalar(15, 230, 200)};
    const ColorFilter yellow = ColorFilter{2, cv::Scalar(30, 80, 80), cv::Scalar(60, 245, 245)};

    const std::vector<ColorFilter> colours = {yellow, red, green};

    std::vector<Card> cards;

    void Initialize();

    /**
     * @brief Returns the Gauss filtered img to be further used in object classification
     * @param input_img is the original video capture that needs to be converted.
     * @return The blurred img.
     */
    static cv::Mat GetBlurredImage(const cv::Mat& input_img);

    /**
     * @brief Converts the img colour spectrum from HSV to RGB
     * @param img blurred image that needs to be colour converted
     * @param color Colour filter associated with the detected image
     * @return The colour converted image to be used for blob filtering
     */
    static cv::Mat GetFilteredImage(const cv::Mat *img, const ColorFilter &color);

    /**
     * @brief Based on the Colour filter detects the desired blob, data of the blob gets passed to a card structure
     * @param img final image to use for blob filtering
     * @param color the colour filter associated with the image for e.g. red filter for detecting red blobs (cards)
     * @return A list of cards to use in @Spawner
     */
    std::vector<CardDetector::Card> FilterTheBlob(const cv::Mat *img, const ColorFilter& color);

    /**
     * @brief Prints the data of a card
     */
    static void PrintCard(Card& card);

    /**
     * @brief based on the detected colour return the associated RGB value
     * @param colorCode incoming colour that has been detected
     * @return A pure @red, @green or @yellow value
     */
    static cv::Scalar GetColor(unsigned int colorCode);
};