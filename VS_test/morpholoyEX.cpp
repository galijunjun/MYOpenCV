#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define ed "腐蚀/膨胀"
#define oc "开/闭"
#define tb "顶帽/黑帽"

Mat src,dst;
int value=10,max_value=value*2+1;
int num_ed=10,num_oc=10,num_tb=10;
int type;
void on_ed(int,void*);//腐蚀或者膨胀操作
void on_oc(int,void*);//开闭操作
void on_tb(int,void*);//顶帽或者黑帽操作

int main()
{
    src=imread("hjy.jpg");
    imshow("原图",src);

    namedWindow(ed,1);
    createTrackbar("e/d=",ed,&num_ed,max_value,on_ed);

    namedWindow(oc,1);
    createTrackbar("o/c=",oc,&num_oc,max_value,on_oc);

    namedWindow(tb,1);
    createTrackbar("t/p=",tb,&num_tb,max_value,on_tb);

    while(1)
    {
        on_ed(num_ed,0);
        on_oc(num_oc,0);
        on_tb(num_tb,0);

        char c=waitKey(1);
        if(c=='q')
            break;
        else if(c=='1')
            type=MORPH_ELLIPSE;
        else if(c=='2')
            type=MORPH_RECT;
        else if(c=='3')
            type=MORPH_CROSS;
        else if(c==' ')
            type=(type+1)%3;
    }
    return 0;

}

void on_ed(int,void*)//腐蚀或者膨胀操作
{
    dst=src.clone();
    int num=num_ed-value;
    int absnum=num>0?num:-num;
    Mat e=getStructuringElement(type,Size(absnum*2+1,absnum*2+1),Point(absnum,absnum));
    if(num>0)
        dilate(src,dst,e);
    else
        erode(src,dst,e);
    imshow(ed,dst);
    
}

void on_oc(int,void*)//开闭操作
{
    dst=src.clone();
    int num=num_oc-value;
    int absnum=num>0?num:-num;
    Mat e=getStructuringElement(type,Size(absnum*2+1,absnum*2+1),Point(absnum,absnum));
    if(num>0)
        morphologyEx(src,dst,MORPH_OPEN,e);
    else
        morphologyEx(src,dst,MORPH_CLOSE,e);  
    imshow(oc,dst);
    
}
void on_tb(int,void*)//顶帽或者黑帽操作
{
    dst=src.clone();
    int num=num_tb-value;
    int absnum=num>0?num:-num;
    Mat e=getStructuringElement(type,Size(absnum*2+1,absnum*2+1),Point(absnum,absnum));
    if(num>0)
        morphologyEx(src,dst,MORPH_TOPHAT,e);
    else
        morphologyEx(src,dst,MORPH_BLACKHAT,e);
    imshow(tb,dst);
    
}