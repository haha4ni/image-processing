#include "hough.h"

using namespace std;
using namespace cv;

const int edge_color = 255;
const double radian = CV_PI / 180;

void HoughLinesHaha(Mat& source, vector<Vec2f>& lines, double rho, double theta, int threshold)
{
	int image_w = source.cols;
	int image_h = source.rows;
	uchar* image_data = source.data;

	lines.clear();

	//左上為0點 右邊為0度 左邊為179度 右(0)->下(89)->左(179)
	int hough_h = cvCeil(((sqrt(image_w*image_w + image_h * image_h)))/rho);
	int accu_h = cvCeil((hough_h * 2.0));
	int accu_w = CV_PI/theta;

	//int* accu = (int*)calloc(accu_h * accu_w, sizeof(int));
	Mat accu_m(accu_h, accu_w, CV_32S, Scalar(0));//代替calloc
	int* accu_md = (int*)accu_m.data;

	// r-theta space accumulate
	// r|
	//  |
	//  |______
	//       theta
	for (int y = 0; y < image_h; y++)
		for (int x = 0; x < image_w; x++)
			if (image_data[(y*image_w) + x] == edge_color)
				for (double t = 0; t < CV_PI-theta; t += theta)
				{
					int r = cvRound((x * cos(t) + y * sin(t)) / rho);
					int mdx = cvRound(t / theta);
					int mdy = (r + hough_h) * accu_w;//hough_h : offset
					accu_md[mdy + mdx] += 1;
				}

	//高於閾值轉換成線收納
	for (int r = 0; r < accu_h; r++)
		for (int t = 0; t < accu_w; t++)
			if ((int)accu_md[(r*accu_w) + t] >= threshold)
				lines.push_back(Vec2f((r- hough_h)*rho,t*theta));


	Mat rt_space;
	accu_m.convertTo(rt_space, CV_8UC1);
	Mat rt_space_roiA = rt_space(Rect(0, 0, accu_w, hough_h));
	Mat rt_space_roiB = rt_space(Rect(0, hough_h, accu_w, hough_h));
	imshow("roiA", rt_space_roiA);
	imshow("roiB", rt_space_roiB);
}