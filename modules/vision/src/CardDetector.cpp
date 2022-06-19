/**
 * @file
 * @brief Source file for the CardDetector class
 * @author tjtle
 * @date 13-05-2022
 */

#include "CardDetector.h"
#include <vector>
#include <iostream> //Dit is ffe voor debug waardes bekijken



cv::Mat CardDetector::GetBlurredImage(const cv::Mat &input_img)
{
    cv::Mat output_img;

    cv::GaussianBlur(input_img, output_img, cv::Size(29, 29), 29);
    return output_img;
}

cv::Mat CardDetector::GetFilteredImage(const cv::Mat *img, const ColorFilter &color)
{
    cv::Mat hsv_img, mask_img, output_img;

    cvtColor(*img, hsv_img, cv::COLOR_BGR2HSV_FULL);
    inRange(hsv_img, color.low, color.high, mask_img);
    bitwise_and(hsv_img, hsv_img, output_img, mask_img);
    cvtColor(output_img, output_img, cv::COLOR_HSV2BGR_FULL);
    return output_img;
}

std::vector<CardDetector::Card> CardDetector::FilterTheBlob(const cv::Mat *img, const ColorFilter &color)
{
    std::vector<CardDetector::Card> result;

    cv::Mat grey_img;
    cv::cvtColor(*img, grey_img, cv::COLOR_HSV2RGB_FULL);
    cv::cvtColor(grey_img, grey_img, cv::COLOR_RGB2GRAY);

    cv::threshold(grey_img, grey_img, 1, 255, cv::THRESH_BINARY);

    //Setting up blob filter params
    cv::SimpleBlobDetector::Params blob_detector_params;

    blob_detector_params.minThreshold = 0;
    blob_detector_params.maxThreshold = 255;
    blob_detector_params.minDistBetweenBlobs = 0;

    //Setup which colours need to be filtered to
    blob_detector_params.filterByColor = false;
    blob_detector_params.blobColor = 0;

    //Setup which areas are to be filtered
    blob_detector_params.filterByArea = true;
    blob_detector_params.minArea = 400;
    blob_detector_params.maxArea = 500000;


    //Setup which shapes need to be filtered
    blob_detector_params.filterByCircularity = true;
    blob_detector_params.minCircularity = 0;
    blob_detector_params.maxCircularity = 0.785;

    //Setting up blob detector
    cv::Ptr<cv::SimpleBlobDetector> blob_detector = cv::SimpleBlobDetector::create(
            blob_detector_params);

    //Detect blobs and store their key-points
    std::vector<cv::KeyPoint> key_points;
    blob_detector->detect(grey_img, key_points);

    cv::Mat img_with_keypoints;
    cv::drawKeypoints(grey_img, key_points, img_with_keypoints, cv::Scalar(0, 0, 255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    //Met een for-loop de info uit de vector halen.
    for (auto &key_point: key_points)
    {
        Card card = {color.color, key_point.pt.x / img_with_keypoints.cols, key_point
                              .pt.y / img_with_keypoints.rows};
        result.push_back(card);
    }

    return result;
}

cv::Mat CardDetector::UpdateCards(const cv::Mat &input_image)
{
    if (!initialized) Initialize();

    std::vector<CardDetector::Card> detectedCards;

    // Detect new cards
    cv::Mat temp, temp2;
    temp = GetBlurredImage(input_image);
    for (const auto &color: colours)
    {
        temp2 = GetFilteredImage(&temp, color);
        detectedCards = FilterTheBlob(&temp2, color);
        if(detectedCards.data())
            break; //If a card has been detected break out of loop, draw it
    }

    this->cardsUpdateLock.lock();

    // empty and update list with old cards
    cards.clear();
    cards = detectedCards;

    this->cardsUpdateLock.unlock();

    for (const auto &card: cards)
    {
        cv::circle(input_image, cv::Point((int) (card.x * input_image.cols), (int) (card.y * input_image.rows)),
                   40, GetColor(card.color), 4);
    }
    return input_image;
}

std::vector<CardDetector::Card> CardDetector::GetDetectedCards()
{
    std::vector<CardDetector::Card> result;

    this->cardsUpdateLock.lock();
    result = this->cards;
    this->cardsUpdateLock.unlock();

    return result;
}

void CardDetector::PrintCard(Card& card)
{
    std::cout << "Color: " << card.color << " Position: " << card.x << "," << card.y << "\n";
}

void CardDetector::PrintCards()
{
    this->cardsUpdateLock.lock();

    if (cards.empty())
    {
        //std::cout << "empty\n";
        return;
    }
    for (auto &card: cards)
    {
        PrintCard(card);
    }

    this->cardsUpdateLock.unlock();
}

void CardDetector::Initialize()
{
    initialized = true;
}

cv::Scalar CardDetector::GetColor(unsigned int colorCode)
{
    if (colorCode == 0) return {0, 255, 0};
    if (colorCode == 1) return {0, 0, 255};
    if (colorCode == 2) return {0, 255, 255};
    return {0, 0, 0};
}

////        cv::Mat red_mask1 = add_filter(&loaded_img,
////                                       cv::Scalar(245, 190, 100), cv::Scalar (255, 230,200)); //red
////        cv::Mat red_mask2 = add_filter(&loaded_img,
////                                       cv::Scalar(0, 190, 100),
////                                       cv::Scalar (12, 230,200)); //red
////        cv::Mat red_output;
////        cv::bitwise_or(red_mask1, red_mask2, red_output);
