#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int mode=1;//读取图片的方式
void onchange(int,void *);
int main()
{
    namedWindow("show",WINDOW_AUTOSIZE);
    createTrackbar("mode","show",&mode,2,onchange);
    //滑块移动的范围永远都是[0,maxval],第三个参数是指定从哪个位置开始滑动
    onchange(0,0);//初始化，这样才能一开始就显示，否则是黑屏

    waitKey(0);//妈的，原来是没加这个，所以显示不了图片
    return 0;
}
void onchange(int,void *)
{
    Mat src=imread("test.jpeg",mode-1);//因为输入必须是int型
    if(!src.data)
    {
       cout<<"figure load error!";
    }
    imshow("show",src);
}
