#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define WINSIZE 500
void draw_line(Mat img,Point s,Point e);
void draw_ellipse(Mat img,double angle);
void draw_circle(Mat img,Point c,int r);
int main()
{
    Mat src(WINSIZE,WINSIZE,CV_8UC3,Scalar::all(0));
    draw_line(src,Point(10,10),Point(WINSIZE/2,WINSIZE/2));
    draw_ellipse(src,90);
    draw_circle(src,Point(src.cols/3*2,src.rows/3*2),100);
    rectangle(src,Rect(WINSIZE/5,WINSIZE/5,WINSIZE/6,WINSIZE/6),Scalar(1,3,55),-1);
    imshow("fig",src);
    waitKey(0);
    return 0;
}
void draw_line(Mat img,Point s,Point e)
{
    line(img,s,e,Scalar(0,0,255),2);
}
void draw_ellipse(Mat img,double angle)
{
    int thickness=2;
    int lineType=8;
    ellipse(img,Point(WINSIZE/2,WINSIZE/2),Size(WINSIZE/4,WINSIZE/16),angle,0,360,Scalar(255,0,0),thickness,lineType);
}
void draw_circle(Mat img,Point c,int r)
{
    circle(img,c,r,Scalar(0,255,0),-1);
}