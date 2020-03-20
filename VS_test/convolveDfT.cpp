#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

void convolveDFT(Mat a,Mat b,Mat &c);
int main()
{
    Mat B=(Mat_<float>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
    //卷积核
    Mat A=imread("zx.jpg",0);
    imshow("img",A);
    A=Mat_<float>(A);
    //dft的时候必须要求是３２位浮点型数据
    Mat C;
    convolveDFT(A,B,C);//卷积
    normalize(C,C,0,1,CV_MINMAX);
    imshow("filtered",C);
    //cout<<"A*B="<<format(C,Formatter::FMT_PYTHON)<<endl;
    waitKey(0);
    return 0;
}
void convolveDFT(Mat a,Mat b,Mat &c)
{
    c.create(abs(a.rows-b.rows)+1,abs(a.cols-b.cols)+1,a.type());
    Size dsize;
    dsize.width=getOptimalDFTSize(a.cols+b.cols-1);
    dsize.height=getOptimalDFTSize(a.rows+b.rows-1);

    Mat tempa(dsize,a.type(),Scalar::all(0));
    Mat tempb(dsize,b.type(),Scalar::all(0));

    Mat roia(tempa,Rect(0,0,a.cols,a.rows));
    a.copyTo(roia);
    Mat roib(tempb,Rect(0,0,b.cols,b.rows));
    b.copyTo(roib);

    dft(tempa,tempa,0,a.rows);
    dft(tempb,tempb,0,b.rows);
    
    mulSpectrums(tempa,tempb,tempa,DFT_COMPLEX_OUTPUT);

    dft(tempa,tempa,DFT_INVERSE+DFT_SCALE,c.rows);
    //傅里叶反变换

    tempa(Rect(0,0,c.cols,c.rows)).copyTo(c);



}