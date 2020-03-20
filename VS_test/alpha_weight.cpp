#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int alpha=10;
int max_alpha=100;
Mat src1;
Mat src2;
Mat roi;
Mat dst;
char barname[50];
void onchange(int,void*);
int main()
{
    src1=imread("fj1.jpeg");
    src2=imread("fj2.jpg");
    imshow("1",src1);
    imshow("2",src2);
    cout<<src1.rows<<" "<<src1.cols<<endl;
    cout<<src2.rows<<" "<<src2.cols<<endl;
    if(src1.rows==src2.rows && src1.cols==src2.cols)
        roi=src1;
    else{
        resize(src1,roi,Size(),(double)src2.cols/src1.cols,(double)src2.rows/src1.rows);
        //src1变成src2的尺寸

        //roi=src2(Range(0,src1.rows),Range(0,src1.cols));
        //因为线性混合的时候需要两个源图像尺寸相同，所以这里用roi的方式去一个区域
    }


    namedWindow("mixed",WINDOW_AUTOSIZE);
    
    sprintf(barname,"alpha value:%d",alpha);
    createTrackbar(barname,"mixed",&alpha,max_alpha,onchange);
    onchange(0,0);
    
    waitKey(0);
    return 0;
}
void onchange(int,void*)
{
    addWeighted(roi,(double)alpha/max_alpha,src2,(double)1-alpha/max_alpha,0,dst);
    imshow("mixed",dst);
    cout<<"当前alpha的值＝"<<(double)getTrackbarPos(barname,"mixed")/100<<endl;
    //获得当前轨迹条的位置　int
}