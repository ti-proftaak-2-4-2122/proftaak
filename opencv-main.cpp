//
// Created by twanh on 11-5-2022.
//

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>

using namespace cv;

int main() {
    VideoCapture cap(1);
    Mat img;

    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1);
    }
}