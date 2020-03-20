//图像傅里叶变换，先扩充，再傅里叶变换，求幅值，变范围，移动到中心，归一化
#include<iostream>
#include<opencv2/opencv.hpp>
//#include "Cshift.h"

using namespace std;
using namespace cv;

void circshift(Mat &out, const Point &delta);
void fftshift(Mat &out);

int main()
{
    Mat img=imread("hjy.jpg",0);//必须为单通道图像
    //如果是多通道，那么就每个通道依次进行傅里叶变换
    imshow("img",img);
/*
    //对图像进行旋转操作
    Point2f center((float)(img.cols/2),(float)img.rows/2);
    Mat affine_matrix = getRotationMatrix2D( center, 30, 1.0 );//求得旋转矩阵 '
    warpAffine(img, img, affine_matrix, img.size());
    imshow("img_roate",img);

*/

    //获得最佳尺寸
    int m=getOptimalDFTSize(img.rows);
    int n=getOptimalDFTSize(img.cols);

    //边界填充，用０填充
    Mat padded;
    copyMakeBorder(img,padded,0,m-img.rows,0,n-img.cols,BORDER_CONSTANT,Scalar::all(0));

    //数据类型转化，为傅里叶变换分配储存空间，实部和虚部
    Mat planes[]={Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F)};//必须要float类型的数据
    Mat complexI;
    merge(planes,2,complexI);

    //进行dft
    dft(complexI,complexI);

    //求幅值图像
    split(complexI,planes);
    magnitude(planes[0],planes[1],planes[0]);
    Mat magnitudeI=planes[0];


    //对数尺度缩放，幅度变化范围太大，不方便在屏幕上显示，因此用对数尺度代替线性尺度，这样变化范围会小一点
    //log(M+1)
    magnitudeI+=Scalar::all(1);
    log(magnitudeI,magnitudeI);


    //将四个角转移至图像中间，为了方便显示
    //因为幅值图像具有平移性，这样转移可以方便可视化

/*
    magnitudeI=magnitudeI(Rect(0,0,magnitudeI.cols&-2,magnitudeI.rows&-2));
    //如果是奇数，就减一变成偶数
    
    int cx=magnitudeI.cols/2;
    int cy=magnitudeI.rows/2;
    Mat q0=magnitudeI(Rect(0,0,cx,cy));
    Mat q1=magnitudeI(Rect(cx,0,cx,cy));
    Mat q2=magnitudeI(Rect(0,cy,cx,cy));
    Mat q3=magnitudeI(Rect(cx,cy,cx,cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    //左上和右下调换位置

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    //右上和左下调换

*/
    fftshift(magnitudeI);

    //幅值变换范围还是过大，归一化到[0,1]可显示范围
    normalize(magnitudeI,magnitudeI,0,1,NORM_MINMAX);


    imshow("dft_img",magnitudeI);


    waitKey(0);
    return 0;
}


void circshift(Mat &out, const Point &delta)
{
    Size sz = out.size();

    // 错误检查
    assert(sz.height > 0 && sz.width > 0);
    // 此种情况不需要移动
    if ((sz.height == 1 && sz.width == 1) || (delta.x == 0 && delta.y == 0))
        return;

    // 需要移动参数的变换，这样就能输入各种整数了
    int x = delta.x;
    int y = delta.y;
    if (x > 0) x = x % sz.width;
    if (y > 0) y = y % sz.height;
    if (x < 0) x = x % sz.width + sz.width;
    if (y < 0) y = y % sz.height + sz.height;


    // 多维的Mat也能移动
    vector<Mat> planes;
    split(out, planes);

    for (size_t i = 0; i < planes.size(); i++)
    {
        // 竖直方向移动
        Mat tmp0, tmp1, tmp2, tmp3;
        Mat q0(planes[i], Rect(0, 0, sz.width, sz.height - y));
        Mat q1(planes[i], Rect(0, sz.height - y, sz.width, y));
        q0.copyTo(tmp0);
        q1.copyTo(tmp1);
        tmp0.copyTo(planes[i](Rect(0, y, sz.width, sz.height - y)));
        tmp1.copyTo(planes[i](Rect(0, 0, sz.width, y)));

        // 水平方向移动
        Mat q2(planes[i], Rect(0, 0, sz.width - x, sz.height));
        Mat q3(planes[i], Rect(sz.width - x, 0, x, sz.height));
        q2.copyTo(tmp2);
        q3.copyTo(tmp3);
        tmp2.copyTo(planes[i](Rect(x, 0, sz.width - x, sz.height)));
        tmp3.copyTo(planes[i](Rect(0, 0, x, sz.height)));
    }

    merge(planes, out);
}

void fftshift(Mat &out)
{
    Size sz = out.size();
    Point pt(0, 0);
    pt.x = (int)floor(sz.width / 2.0);
    pt.y = (int)floor(sz.height / 2.0);
    circshift(out, pt);
}