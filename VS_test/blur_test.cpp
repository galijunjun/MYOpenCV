//这是对opencv中图像模糊的ＡＰＩ测试

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
//全局变量
int box_s=3;
int mean_s=3;
int gaussian_s=3;
int median_s=3;
int bil_s=3;
int maxv=100;
Mat src,box_I,mean_I,gaussian_I,median_I,bil_I;

//回调函数
static void onchange_box(int,void*);
static void onchange_mean(int,void*);
static void onchange_gaussian(int,void*);
static void onchange_median(int,void*);
static void onchange_bil(int,void*);
/*
在函数的返回类型前加上关键字static，函数就被定义成为静态函数。
普通函数的定义和声明默认情况下是extern的，但静态函数只是在声明他的文件当中可见，不能被其他文件所用。
因此定义静态函数有以下好处：
<1> 其他文件中可以定义相同名字的函数，不会发生冲突。
<2> 静态函数不能被其他文件所用。
*/

int main()
{
    system("color 1E");

    src=imread("fw.jpg");
    if(!src.data)
    {
        cout<<"读取图片出错！"<<endl;
        return -1;
    }
    //src.convertTo(src,CV_32F);
    imshow("原图",src);
    //cout<<src.rows<<" "<<src.cols<<endl;

    box_I=src.clone();
    mean_I=src.clone();
    gaussian_I=src.clone();
    median_I=src.clone();
    bil_I=src.clone();
  
    //方框滤波
    namedWindow("1方框滤波",WINDOW_AUTOSIZE);
    createTrackbar("ksize","1方框滤波",&box_s,maxv,onchange_box);
    onchange_box(box_s,0);
    imshow("1方框滤波",box_I);

    //均值滤波
    namedWindow("2均值滤波",1);
    createTrackbar("ksize","2均值滤波",&mean_s,maxv,onchange_mean);  
    onchange_mean(mean_s,0);

    //高斯滤波
    namedWindow("3高斯滤波",1);
    createTrackbar("ksize","3高斯滤波",&gaussian_s,maxv,onchange_gaussian);
    onchange_gaussian(gaussian_s,0);

    //中值滤波
    namedWindow("4中值滤波",1);
    createTrackbar("ksize","4中值滤波",&median_s,maxv,onchange_median);
    onchange_median(median_s,0);

    //双边滤波
    namedWindow("5双边滤波",1);
    createTrackbar("ksize","5双边滤波",&bil_s,maxv,onchange_bil);
    onchange_bil(bil_s,0);


    while(char(waitKey(1))!='q'){}
    return 0;
}

static void onchange_box(int,void*)
{
    boxFilter(src,box_I,-1,Size(box_s+1,box_s+1));
    imshow("1方框滤波",box_I);
}
static void onchange_mean(int,void*)
{
    blur(src,mean_I,Size(mean_s+1,mean_s+1));
    imshow("2均值滤波",mean_I);
}
static void onchange_gaussian(int,void*)
{
    GaussianBlur(src,gaussian_I,Size(gaussian_s*2+1,gaussian_s*2+1),0,0);
    imshow("3高斯滤波",gaussian_I);

}
static void onchange_median(int,void*)
{
    medianBlur(src,median_I,median_s*2+1);
    imshow("4中值滤波",median_I);
}
static void onchange_bil(int,void*)
{
    bilateralFilter(src,bil_I,bil_s,bil_s*2,bil_s/2);
    imshow("5双边滤波",bil_I);
}