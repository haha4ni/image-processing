#ifndef HOUGH_H
#define HOUGH_H

#include <opencv2/opencv.hpp>

void HoughLinesHaha(cv::Mat &image, std::vector<cv::Vec2f> &lines, double rho, double theta, int threshold);

#endif