//
// Created by tjtle on 13/05/2022.
//

#include "ImageFilter.h"
#include <vector>
#include <iostream> //Dit is ffe voor debug waardes bekijken

void ImageFilter::add_filters(cv::Mat *img)
{
    cvtColor(*img, hsv_img, cv::COLOR_BGR2HSV_FULL);
    cv::Scalar hsv_l(100, 80, 80);
    cv::Scalar hsv_h(200, 240, 200);

    inRange(hsv_img, hsv_l, hsv_h, mask_img);
    bitwise_and(hsv_img, hsv_img, output_img, mask_img);
    //cv::resize(hsv_img, hsv_img, cv::Size(), 1000, 1000);
    cvtColor(output_img, output_img, cv::COLOR_HSV2BGR_FULL);
    cv::imshow("output", output_img);
    cv::waitKey(1);
}

void ImageFilter::filter_the_blob(cv::Mat *img)
{
//    cv::Mat colour_img = *img;
//    cv::cvtColor(*img, colour_img, cv::COLOR_BGR2RGB);

    cv::bitwise_not(*img, *img);

    //Setting up blob filter params
    cv::SimpleBlobDetector::Params blob_detector_params;

    blob_detector_params.minThreshold = 50;
    blob_detector_params.maxThreshold = 200;

    //Setup which colours need to be filtered to
    blob_detector_params.filterByColor = true;
    blob_detector_params.blobColor = 200;

    //Setup which areas are to be filtered
//    blob_detector_params.filterByArea = true;
//    blob_detector_params.minArea = 50;

    //Setup which shapes need to be filtered
//    blob_detector_params.filterByCircularity = true;
//    blob_detector_params.minCircularity = 0;
//    blob_detector_params.maxCircularity = 0.785;



    //Setting up blob detector
    cv::Ptr<cv::SimpleBlobDetector> blob_detector = cv::SimpleBlobDetector::create(
            blob_detector_params);

    //Detect blobs and store their key-points
    std::vector<cv::KeyPoint> key_points;
    blob_detector->detect(*img, key_points);

    cv::Mat img_with_keypoints;
    cv::drawKeypoints(*img, key_points, img_with_keypoints, cv::Scalar(0, 255, 255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    //Met een for-loop de info uit de vector halen.

    for (auto blob_iterator = key_points.begin(); blob_iterator != key_points.end();
         blob_iterator++)
    {
        std::cout << " Size of blob: " << blob_iterator->size << std::endl;
        std::cout << " Point x of blob: " << blob_iterator->pt.x << "\t" << "Point y of blob: " <<
                  blob_iterator->pt.y << std::endl;
    }

    cv::imshow("Blob filter", img_with_keypoints);
//    cv::imshow("grey scaled img", colour_img);
//    cv::waitKey(0);
}


void ImageFilter::filter_image()
{
//    std::string path = "../resources/hsv.jpg";
//    loaded_img = cv::imread(path);

    cv::VideoCapture cap(0);

    while (true)
    {
        cap.read(loaded_img);
        add_filters(&loaded_img);
        filter_the_blob(&output_img);
        cv::imshow("original", loaded_img);
        cv::waitKey(10);
    }

    cv::imshow("Image", loaded_img);
    cv::waitKey(0);
}
