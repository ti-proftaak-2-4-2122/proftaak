//
// Created by tjtle on 13/05/2022.
//

#include "ImageFilter.h"
#include <vector>
#include <iostream> //Dit is ffe voor debug waardes bekijken

cv::Mat ImageFilter::add_filter(cv::Mat* img, cv::Scalar hsv_lowerbound, cv::Scalar hsv_upperbound)
{
    cv::Mat loaded_img, hsv_img, mask_img, output_img;

    cvtColor(*img, hsv_img, cv::COLOR_BGR2HSV_FULL);

    inRange(hsv_img, hsv_lowerbound , hsv_upperbound, mask_img);
    bitwise_and(hsv_img, hsv_img, output_img, mask_img);
    cvtColor(output_img, output_img, cv::COLOR_HSV2BGR_FULL);
    return output_img;
}

void ImageFilter::filter_the_blob(cv::Mat *img)
{
    cv::Mat colour_img = *img;
    cv::cvtColor(*img, colour_img, cv::COLOR_HSV2RGB_FULL);

    cv::bitwise_not(colour_img, colour_img);

    //Setting up blob filter params
    cv::SimpleBlobDetector::Params blob_detector_params;

    blob_detector_params.minThreshold = 100;
    blob_detector_params.maxThreshold = 200;

    //Setup which colours need to be filtered to
//    blob_detector_params.filterByColor = true;
//    blob_detector_params.blobColor = 0;

    //Setup which areas are to be filtered
    blob_detector_params.filterByArea = true;
    blob_detector_params.minArea = 50;

    //Setup which shapes need to be filtered
//    blob_detector_params.filterByCircularity = true;
//    blob_detector_params.minCircularity = 0;
//    blob_detector_params.maxCircularity = 0.785;



    //Setting up blob detector
    cv::Ptr<cv::SimpleBlobDetector> blob_detector = cv::SimpleBlobDetector::create(blob_detector_params);

    //Detect blobs and store their key-points
    std::vector<cv::KeyPoint> key_points;
    blob_detector->detect(colour_img,key_points);

    cv::Mat img_with_keypoints;
    cv::drawKeypoints(*img, key_points, img_with_keypoints, cv::Scalar(0, 0, 0),
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
    cv::VideoCapture cap(0);
//    std::string path = "../resources/vormen.jpg";
//    loaded_img = cv::imread(path);
//
//    filter_the_blob(&loaded_img);


    while (1)
    {
        cap.read(loaded_img);
        cv::Mat green_mask = add_filter(&loaded_img,
                                        cv::Scalar(80, 100, 100),
                                        cv::Scalar (120, 200,200)); //green
//        cv::imshow("green", green_mask);

        cv::Mat red_mask1 = add_filter(&loaded_img,
                                       cv::Scalar(240, 150, 100),
                                       cv::Scalar (255, 220,200)); //red
        cv::Mat red_mask2 = add_filter(&loaded_img,
                                       cv::Scalar(0, 150, 100),
                                       cv::Scalar (12, 220,200)); //red
        cv::Mat red_output;
        cv::bitwise_or(red_mask1, red_mask2, red_output);
//        cv::imshow("red", red_output);

        cv::Mat blue_mask = add_filter(&loaded_img,
                                       cv::Scalar(25, 100, 100),
                                       cv::Scalar (55, 200, 200)); //blue
//        cv::imshow("blue", blue_mask);

        filter_the_blob(&red_mask1);
        cv::imshow("original", loaded_img);
        cv::waitKey(10);
    }
}
