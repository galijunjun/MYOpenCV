#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main()
{
    Mat src1=imread("zx.jpg",1);
    cout<<src1.cols<<" "<<src1.rows<<endl;
    Mat src2=imread("kj.jpg",1);
    cout<<src2.cols<<" "<<src2.rows<<endl;

    imshow("zx",src1);
    imshow("kj",src2);
    //Mat roi=src1(Rect(50,50,src2.cols,src2.rows));
    Mat roi=src1(Range(80,80+src2.rows),Range(50,50+src2.cols));
    //两种方法定义roi
    addWeighted(roi,0.5,src2,0.5,0,roi);
    imshow("mixed",roi);
    waitKey(0);
    return 1;
}