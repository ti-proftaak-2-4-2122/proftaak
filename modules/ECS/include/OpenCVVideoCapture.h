//
// Created by twanh on 13-5-2022.
//

#ifndef PROFTAAK24_OPENCVVIDEOCAPTURE_H
#define PROFTAAK24_OPENCVVIDEOCAPTURE_H

#include <memory>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Component.h"

class OpenCVVideoCapture : public Component
{
private:
    std::shared_ptr<cv::VideoCapture> capture;

    uint captureTextureId;

public:
    OpenCVVideoCapture(std::shared_ptr<cv::VideoCapture> capture);

    void Awake() override;
    void Update() override;
    void Draw() override;

};


#endif //PROFTAAK24_OPENCVVIDEOCAPTURE_H
