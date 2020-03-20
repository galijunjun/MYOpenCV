#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

void gen_alpha(Mat &src)
{
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            Vec4b& rgba=src.at<Vec4b>(i,j);
            rgba[0]=UCHAR_MAX;
            rgba[1]=saturate_cast<uchar>((float)(src.cols-i)/(src.cols)*UCHAR_MAX);
            rgba[2]=saturate_cast<uchar>((float)(src.rows-i)/(src.rows)*UCHAR_MAX);
            rgba[3]=saturate_cast<uchar>((float)rgba[1]*0.5+rgba[2]*0.5);
        }
}

int main()
{
    Mat src(480,640,CV_8UC4);
    gen_alpha(src);

    vector<int> compress_params;
    compress_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    int para=5;
    //0~9，默认３
    compress_params.push_back(9);   

    try
    {
        imshow("生成的ＰＮＧ",src);
        imwrite("生成ＰＮＧ.png",src,compress_params);//压缩
        cout<<"生成图片成功"<<endl;
        waitKey(0);
    }
    catch(runtime_error & ex){
        cout<<"出现错误："<<ex.what()<<endl;
    }
    return 1;
}

　