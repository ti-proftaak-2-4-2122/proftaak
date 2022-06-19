/**
 * @file
 * @brief Header file for the OpenCVVideoCapture class
 * @author twanh
 * @date 13-05-2022
 */

#pragma once

#include <memory>
#include <thread>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Component.h"
#include "CardDetector.h"

/**
 * @class Gets the Image from the videoCapture, does this independently
 * Passes OpenCV VideoCapture to CardDetector, to filter the cards based on colour and detect the card objects.
 */
class ImageProvider
{
public:
    explicit ImageProvider(std::shared_ptr<cv::VideoCapture> capture);

    void Awake();

    void Update();

    void Draw() const;

    ~ImageProvider();

private:
    std::shared_ptr<cv::VideoCapture> capture;
    CardDetector *detector = CardDetector::GetInstance();
    uint captureTextureId;

    cv::Mat imageBuffer1;
    cv::Mat imageBuffer2;

    std::thread imageUpdateThread;
    std::mutex imageUpdateLock;

    bool useImageBuffer2 = false;
    bool imageHasUpdated = false;

    bool isDestructing = false;

    void ImageUpdateTask();
    void ReadImage();

};