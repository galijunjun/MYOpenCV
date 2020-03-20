#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int gaussian_s=3;
int median_s=3;
Mat src,dst_g,dst_p;

void gaussian_change(int,void*);
void median_change(int,void*);
Mat noise_gaussian(Mat src,int a,int b);
Mat noise_pulse(Mat src);

int main()
{
    src=imread("hjy_1.png");
    imshow("原图",src);

    dst_g=noise_gaussian(src,10,30);
    imshow("高斯噪声",dst_g);

    namedWindow("高斯滤波",1);
    createTrackbar("ksize","高斯滤波",&gaussian_s,20,gaussian_change);
    gaussian_change(0,0);

    dst_p=noise_pulse(src);
    imshow("椒盐噪声",dst_p);

    namedWindow("中值滤波",1);
    createTrackbar("ksize","中值滤波",&median_s,20,median_change);  
    median_change(0,0);


    while(waitKey(1)!='q'){};
    return 0;
}

Mat noise_gaussian(Mat src,int a,int b)
{
    Mat noise(src.size(),src.type());

    RNG rng(time(NULL));
    rng.fill(noise,RNG::NORMAL,a,b);//高斯分布的随机矩阵
    Mat dst;
    add(src,noise,dst);
    return dst;
}

Mat noise_pulse(Mat src)
{
    Mat dst=src.clone();
    int num=dst.cols*dst.rows/4;
    //cout<<num<<endl;
    for(int i=0;i<num;i++)
    {
        RNG rng(i);
        int x=rng.uniform(0,dst.rows);
        //cout<<x<<endl;
        int y=rng.uniform(0,dst.cols);
        int flag=x%2;//确定亮点还是暗点
        //cout<<flag<<endl;
        if(dst.channels()==1)
            if(flag==1)
                dst.at<uchar>(x,y)=255;
            else
                dst.at<uchar>(x,y)=0;
        else
        {
            if(flag)
            {
                dst.at<Vec3b>(x,y)[0]=255;
                dst.at<Vec3b>(x,y)[1]=255;
                dst.at<Vec3b>(x,y)[2]=255;
            }
            else
            {
                dst.at<Vec3b>(x,y)[0]=0;
                dst.at<Vec3b>(x,y)[1]=0;
                dst.at<Vec3b>(x,y)[2]=0;
            }
            
        }      
    }
    return dst;
}
void gaussian_change(int,void*)
{
    Mat d(dst_g.size(),dst_g.type());
    GaussianBlur(dst_g,d,Size(gaussian_s*2+1,gaussian_s*2+1),0,0);
    imshow("高斯滤波",d);
}

void median_change(int,void*)
{
    Mat d(dst_g.size(),dst_g.type());
    medianBlur(dst_p,d,median_s*2+1);
    imshow("中值滤波",d);
}