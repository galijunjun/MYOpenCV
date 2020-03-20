#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int a=0;
Mat src,logo,roi,tar,tmp;
void onchange(int,void*);
int main()
{
    double s=(double)getTickCount();
    src=imread("fj2.jpg");
    tmp=src.clone();
    logo=imread("kj.jpg");
    Mat mask=imread("kj.jpg",0);
    //必须是灰度图
    imshow("原图１",src);
    imshow("mask",mask);
    roi=src(Range(10,10+mask.rows),Range(10,10+mask.cols));
    //在原图上找一个区域用来融合
    logo.copyTo(roi,mask);
    imshow("mix",src);


    tar=tmp(Rect(20,20,logo.cols,logo.rows));
    //赋值，tar变化的话tmp也会跟着变化
    imshow("1",tmp);
    imshow("2",tar);
    imshow("logo",logo);

    namedWindow("图像融合",WINDOW_AUTOSIZE);
    createTrackbar("权重值","图像融合",&a,100,onchange);
    onchange(0,0);
    //初始化

    cout<<"所用时间＝"<<((double)getTickCount()-s)/getTickFrequency()<<"s"<<endl;
    waitKey(0);
    return 0;
}
void onchange(int,void*)
{
    addWeighted(tar,(double)a/100,logo,(double)a/100+0.2,0.0,tar);
    //参数必须要是double类型
    //addWeighted(tar,(double)a/100,logo,1-(double)a/100,0.0,tar);
    imshow("图像融合",tmp);
}