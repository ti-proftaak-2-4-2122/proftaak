//
// Created by twanh on 11-5-2022.
//

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>

int opencv_main() {
    cv::VideoCapture cap(1);
    cv::Mat img;



    while (true) {
        cap.read(img);
        cv::imshow("Image", img);
        cv::waitKey(1);
    }
}