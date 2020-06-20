#include <opencv2/opencv.hpp>
#include <iostream>  
#include "hough.h"

using namespace std;
using namespace cv;

double rho = 1;
double hough_theta = CV_PI / 180;
double hough_threshold = 120;

int main(int argc, char* argv[])
{
	Mat Image = imread("ntust.jpg");
	Mat GrayImage, GaussImage, CannyImage;
	cvtColor(Image, GrayImage, CV_RGB2GRAY);
	GaussianBlur(GrayImage, GaussImage, Size(5, 5), 0, 0);
	Canny(GaussImage, CannyImage, 100, 150);

	vector<Vec2f> Houghlines;
	//OpenCV­ìª©
	HoughLines(CannyImage, Houghlines, rho, hough_theta, hough_threshold);
	for (int i = 0; i < Houghlines.size(); i++)
	{
		float rho = Houghlines[i][0];
		float theta = Houghlines[i][1];
		//printf("rho = %f,theta = %f\n", rho, theta);
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = rho * a;
		double y0 = rho * b;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * a);
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * a);
		line(Image, pt1, pt2, Scalar(0, 0, 255), 1);
	}
	namedWindow("ImageOriginal");
	imshow("ImageOriginal", Image);

	//Hahaª©
	HoughLinesHaha(CannyImage, Houghlines, rho, hough_theta, hough_threshold);
	for (int i = 0; i< Houghlines.size(); i++)
	{
		float rho = Houghlines[i][0];
		float theta = Houghlines[i][1];
		//printf("rho = %f,theta = %f\n", rho, theta);
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = rho * a;
		double y0 = rho * b;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * a);
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * a);
		line(Image, pt1, pt2, Scalar(255, 0, 0), 1);
	}
	namedWindow("ImageHaha");
	imshow("ImageHaha", Image);

	waitKey();
	return 0;
}