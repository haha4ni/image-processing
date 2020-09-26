#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;

double toRadians(double angle)
{
	return angle * CV_PI / 180;
}

// 烏龜 ----------------------------------------------------------------------------------------------------
class Turtle {
public:
	Turtle();

	double angle = 0;  // current angle
	double currentX = 0, currentY = 0;   // current position
	double wx1 = 0, wy1 = 0, wx2 = 0, wy2 = 0; // canvas coordination
	Mat window;

	void setGraphics(Mat& window);
	Mat& getWindow();
	double getCurrentX();
	double getCurrentY();

	void setWindow(double x1, double y1, double x2, double y2);

	void warp(double l);
	void move(double l);
	void moveTo(double x, double y);

	//設定起始座標
	void setPoint(double x, double y);


	void drawPoint(double x, double y);
	void drawLine(double x1, double y1, double x2, double y2);

	void turn(double a);
	void setAngle(double angle);
};

Turtle::Turtle(){}

void Turtle::setGraphics(Mat& window) {
	this->window = window;
}
Mat& Turtle::getWindow()
{
	return window;
}

double Turtle::getCurrentX() {
	return currentX;
}
double Turtle::getCurrentY() {
	return currentY;
}

void Turtle::setWindow(double x1, double y1, double x2, double y2) {
	wx1 = x1;
	wy1 = y1;
	wx2 = x2;
	wy2 = y2;
}

void Turtle::warp(double l) {
	setPoint(currentX + l * cos(toRadians(angle)),
			 currentY + l * sin(toRadians(angle)));
}

void Turtle::move(double l) {
	double x = currentX + l * cos(toRadians(angle));
	double y = currentY + l * sin(toRadians(angle));
	double x1 = (currentX - wx1);
	double y1 = (wy2 - currentY);
	double x2 = (x - wx1);
	double y2 = (wy2 - y);

	line(window, Point(x1, y1), Point(x2, y2), Scalar(255, 0, 0), 1);
	setPoint(x, y);
}

void Turtle::moveTo(double x, double y) {
	double x1 = (currentX - wx1);
	double y1 = (wy2 - currentY);
	double x2 = (x - wx1);
	double y2 = (wy2 - y);

	line(window, Point(x1, y1), Point(x2, y2), Scalar(255, 0, 0), 1);
	setPoint(x, y);
}

void Turtle::setPoint(double x, double y) {
	currentX = x;
	currentY = y;
}

void Turtle::drawPoint(double x, double y) {
	setPoint(x, y);
	moveTo(x, y);
}

void Turtle::drawLine(double x1, double y1, double x2, double y2) {
	setPoint(x1, y1);
	moveTo(x2, y2);
}

void Turtle::turn(double a) {
	angle = angle + a;
	while (angle >= 360)
	{
		angle = angle - 360;
	}
}

void Turtle::setAngle(double angle) {
	this->angle = angle;
}

// ----------------------------------------------------------------------------------------------------

void koch(int n, double leng, Turtle& turtle) {
	if (n == 0) {
		turtle.move(leng);

//		imshow("koch", turtle.getWindow());
//		waitKey(10);
	}
	else {
		koch(n - 1, leng, turtle);
		turtle.turn(60);
		koch(n - 1, leng, turtle);
		turtle.turn(-120);
		koch(n - 1, leng, turtle);
		turtle.turn(60);
		koch(n - 1, leng, turtle);
	}
}

void fern(double leng, double min, double k1, double k2, Turtle& turtle) {
	turtle.move(leng);
	//imshow("keke", turtle.getWindow());
	//waitKey(1);
	if (leng > min) {
		turtle.turn(70.0);
		fern(k2 * leng, min, k1, k2, turtle);
		turtle.turn(-71.0);
		turtle.move(k1 * leng);
		turtle.turn(-69.0);
		fern(k1 * k2 * leng, min, k1, k2, turtle);
		turtle.turn(68.0);
		fern(k1 * k1 * leng, min, k1, k2, turtle);
		turtle.turn(1.0);
		turtle.warp(-k1 * leng);
		turtle.turn(1.0);
	}
	turtle.warp(-leng);
}


int trackballValue = 3;//滑動條的實時值
void on_TrackBall(int, void*) 
{
	Turtle turtle;

	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));
	turtle.setGraphics(img);
	turtle.setWindow(0, 0, 500, 500);
	turtle.setPoint(250-122, 250+61);

	int weight = pow(3, (5 - trackballValue));
	koch(trackballValue, weight, turtle);
	turtle.setAngle(-120);
	koch(trackballValue, weight, turtle);
	turtle.setAngle(-240);
	koch(trackballValue, weight, turtle);
	imshow("koch", img);
}

#define KOCH

int main(int argc, char const *argv[])
{
	Mat img(450, 450, CV_8UC3, Scalar(255, 255, 255));

#ifdef KOCH
	namedWindow("koch", 1);
	createTrackbar("分支度", "Koch", &trackballValue, 5, on_TrackBall);
	on_TrackBall(trackballValue, 0);
#endif
#ifdef FERN
	Turtle turtle;
	turtle.setGraphics(img);
	turtle.setWindow(0, 0, 500, 500);
	turtle.setPoint(250 - 122, 250 + 61);
	fern(30, 0.1, 0.9, 0.3, turtle);
	imshow("Fern", img);
#endif

	waitKey(0);
	return 0;
}