#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void circshift(Mat &out, const Point &delta);
void fftshift(Mat &out);
void ifftshift(Mat &out);