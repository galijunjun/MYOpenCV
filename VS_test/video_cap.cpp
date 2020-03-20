#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>

using namespace std;
using namespace cv;

int i=1;
int main()
{
    VideoCapture cap(0);
    while(1)
    {
        Mat frame;
        cap>>frame;
        imshow("读取视频",frame);
        char c=waitKey(30);
        if(c==27)
            break;
        else if(c=='c')
        {
            char s[20];//需要预先分配内存空间
            sprintf(s,"capfig_%d.png",i);
            imwrite(s,frame);
            cout<<"保存第"<<i<<"张图片"<<endl;
            i++;
        }
    }
    return 0;
}