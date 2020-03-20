#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

//膨胀和腐蚀,形态学梯度初探，结构元素的类型和尺寸不同
int main()
{
    Mat src=imread("fj2.jpg");
    imshow("1原图",src);

    Mat e1=getStructuringElement(MORPH_RECT,Size(5,5));
    Mat d1=src.clone();
    erode(src,d1,e1);
    imshow("2腐蚀",d1);

    Mat d2=src.clone();
    dilate(src,d2,e1);
    imshow("3膨胀",d2);

    Mat e2=getStructuringElement(MORPH_CROSS,Size(5,5));
    Mat d3=src.clone();
    dilate(src,d3,e2);
    imshow("4膨胀",d3);

    Mat e3=getStructuringElement(MORPH_ELLIPSE,Size(5,5));
    Mat d4=src.clone();
    dilate(src,d4,e3);
    imshow("5膨胀",d4);

    Mat d5,d6,d7;
    subtract(d4,d1,d5);
    imshow("基本梯度",d5);//获取图像边缘，基本梯度

    subtract(src,d1,d6);
    imshow("内部梯度",d6);

    namedWindow("外部梯度",0);//这样窗口大小就可以用书包调整了
    subtract(d4,src,d7);
    imshow("外部梯度",d7);  
    while(waitKey(0)!='q'){}
    return 0;
}