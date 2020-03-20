#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

vector<int> table(256);
int inteval=80;
Mat reduce_col1(Mat img);
Mat reduce_col2(Mat img);
Mat reduce_col3(Mat img);

int main()
{
    Mat src=imread("fw.jpg");
    imshow("原图",src);

    for(int i=0;i<256;i++)
        table[i]=i/inteval*inteval;

    double s1=static_cast<double>(getTickCount());
    //静态类型转换,这里需要是double类型
    Mat dst1=reduce_col1(src);
    cout<<"方法1所用时间="<<((double)getTickCount()-s1)/getTickFrequency()<<"秒"<<endl;

    double s2=(double)(getTickCount());
    //静态类型转换,这里需要是double类型
    Mat dst2=reduce_col2(src);
    cout<<"方法2所用时间="<<((double)getTickCount()-s2)/getTickFrequency()<<"秒"<<endl;

    double s3=(double)(getTickCount());
    //静态类型转换,这里需要是double类型
    Mat dst3=reduce_col3(src);
    cout<<"方法3所用时间="<<((double)getTickCount()-s3)/getTickFrequency()<<"秒"<<endl;

    imshow("颜色范围缩减",dst1);
    waitKey(0);
    return 0;
}
//[]方式读取
Mat reduce_col1(Mat img)
{
    Mat dst=img.clone();
    int rows=dst.rows;
    int cols=dst.cols*dst.channels();
    for(int i=0;i<rows;i++)
    {
        uchar* data=dst.ptr<uchar>(i);
        for(int j=0;j<cols;j++)
        {
            data[j]=table[data[j]];
        }
    }
    return dst;
}
//迭代器读取
Mat reduce_col2(Mat img)
{
    Mat dst=img.clone();
    Mat_<Vec3b>::iterator it=dst.begin<Vec3b>();
    Mat_<Vec3b>::iterator iend=dst.end<Vec3b>();
    for(;it!=iend;it++)
    {
        (*it)[0]=table[(*it)[0]];
        (*it)[1]=table[(*it)[1]];
        (*it)[2]=table[(*it)[2]];
    }
    return dst;
}
//动态读取，at
Mat reduce_col3(Mat img)
{
    Mat dst=img.clone();
    for(int i=0;i<dst.rows;i++)
        for(int j=0;j<dst.cols;j++)
        {
            dst.at<Vec3b>(i,j)[0]=table[dst.at<Vec3b>(i,j)[0]];
            dst.at<Vec3b>(i,j)[1]=table[dst.at<Vec3b>(i,j)[1]];
            dst.at<Vec3b>(i,j)[2]=table[dst.at<Vec3b>(i,j)[2]];
        }
    return dst;
}