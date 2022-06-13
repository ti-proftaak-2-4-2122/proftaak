/**
 * @file
 * @brief Header file for the OpenCVVideoCapture class
 * @author twanh
 * @date 13-05-2022
 */

#pragma once

#include <memory>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Component.h"
#include "CardDetector.h"

class ImageProvider
{
private:
    std::shared_ptr<cv::VideoCapture> capture;
    CardDetector *detector = CardDetector::GetInstance();
    uint captureTextureId;

public:
    explicit ImageProvider(std::shared_ptr<cv::VideoCapture> capture);

    void Awake();

    void Update();

    void Draw() const;

    ~ImageProvider();

};