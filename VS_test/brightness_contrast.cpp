#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

#define WINNAME "结果"
int a=10;
int b=10;
int amax=100;
int bmax=100;

Mat src,dst;
void onchange(int,void*);
int main()
{
    src=imread("zx.jpg");
    //多通道分离，merge
    vector<Mat> channels;
    split(src,channels);
    imshow("B",channels.at(0));
    imshow("G",channels.at(1));
    imshow("R",channels.at(2));

    namedWindow(WINNAME,WINDOW_AUTOSIZE);
    createTrackbar("对比度=",WINNAME,&a,amax,onchange);
    createTrackbar("亮度=",WINNAME,&b,bmax,onchange);
    onchange(a,0);
    onchange(b,0);
    //初始化
    waitKey(0);
    return 0;
}
void onchange(int,void*)
{
    dst=src.clone();
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
            for(int c=0;c<3;c++)//各个通道分开计算
                dst.at<Vec3b>(i,j)[c]=saturate_cast<uchar>(src.at<Vec3b>(i,j)[c]*a*0.01+b);
                //saturate_cast为了防止数值溢出
    imshow("原始窗口",src);
    imshow(WINNAME,dst);
}