//
// Created by tjtle on 13/05/2022.
//

#include "ImageFilter.h"
#include <vector>
#include <iostream> //Dit is ffe voor debug waardes bekijken

cv::Mat ImageFilter::add_gaussianblur(const cv::Mat input_img){
    cv::Mat output_img;

    cv::GaussianBlur(input_img, output_img, cv::Size(21, 21), 21);

    return output_img;
}

cv::Mat ImageFilter::add_filter(const cv::Mat* img, const cv::Scalar& hsv_lowerbound, const cv::Scalar&
hsv_upperbound)
{
    cv::Mat hsv_img, mask_img, output_img;

    cvtColor(*img, hsv_img, cv::COLOR_BGR2HSV_FULL);

    inRange(hsv_img, hsv_lowerbound , hsv_upperbound, mask_img);
    bitwise_and(hsv_img, hsv_img, output_img, mask_img);
    cvtColor(output_img, output_img, cv::COLOR_HSV2BGR_FULL);
    return output_img;
}

cv::Mat ImageFilter::filter_the_blob(const cv::Mat *img)
{
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
    cv::Ptr<cv::SimpleBlobDetector> blob_detector = cv::SimpleBlobDetector::create(blob_detector_params);

    //Detect blobs and store their key-points
    std::vector<cv::KeyPoint> key_points;
    blob_detector->detect(grey_img, key_points);

    cv::Mat img_with_keypoints;
    cv::drawKeypoints(grey_img, key_points, img_with_keypoints, cv::Scalar(0, 0, 255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    //Met een for-loop de info uit de vector halen.
    for (auto blob_iterator = key_points.begin(); blob_iterator != key_points.end();
         blob_iterator++)
    {
        std::cout << " Size of blob: " << blob_iterator->size << std::endl;
        std::cout << " Point x of blob: " << blob_iterator->pt.x << "\t" << "Point y of blob: " <<
                  blob_iterator->pt.y << std::endl;
        cv::circle(img_with_keypoints, cv::Point(blob_iterator->pt.x, blob_iterator->pt.y),
                   blob_iterator->size, cv::Scalar(255, 255, 255), 5);
    }
    return img_with_keypoints;
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

        cv::Mat red_mask1 = add_filter(&loaded_img,
                                       cv::Scalar(245, 190, 100),
                                       cv::Scalar (255, 230,200)); //red
        cv::Mat red_mask2 = add_filter(&loaded_img,
                                       cv::Scalar(0, 190, 100),
                                       cv::Scalar (12, 230,200)); //red
        cv::Mat red_output;
        cv::bitwise_or(red_mask1, red_mask2, red_output);

        cv::Mat yellow_mask = add_filter(&loaded_img,
                                       cv::Scalar(25, 100, 100),
                                       cv::Scalar (55, 200, 200)); //yellow

        yellow_mask = add_gaussianblur(yellow_mask);
        cv::imshow("yellowblob", filter_the_blob(&yellow_mask));

        green_mask = add_gaussianblur(green_mask);
        cv::imshow("greenblob", filter_the_blob(&green_mask));

        red_output = add_gaussianblur(red_output);
        cv::imshow("redblob", filter_the_blob(&red_output));
        loaded_img = add_gaussianblur(loaded_img);

        cv::imshow("original", loaded_img);
        cv::waitKey(1);
    }
}
