//鼠标回调函数，读入一张图片，在图片上可用矩形框选择roi并自动保存

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define windowname "原图"
Mat src,dst;
Rect g_rect;//绘制的坐标
RNG g(22);//随机的颜色
bool draw_flag=false;//是否进行绘制
int i=0;

void mouse_back(int event,int x,int y,int flags,void* param);
void draw_rect(Mat& img,Rect box);
void showhelptext(int event);

int main()
{
    src=imread("hjy.jpg");
    src.copyTo(dst);
    Mat tmp;

    namedWindow(windowname,WINDOW_AUTOSIZE);
    setMouseCallback(windowname,mouse_back,&src);
    while(1)
    {
        src.copyTo(tmp);
        if(draw_flag)
            draw_rect(tmp,g_rect);
        imshow(windowname,src);
        if(waitKey(20)==27)
            break;
    }
    return 0;
}
void mouse_back(int event,int x,int y,int flags,void* param)
{
    Mat img=*(Mat*)param;//类型转换
    switch(event)
    {
        case EVENT_MOUSEMOVE:
        {
            if(draw_flag)
            {
                g_rect.width=x-g_rect.x;
                g_rect.height=y-g_rect.y;
            }
        }
        break;
        case EVENT_LBUTTONDOWN:
        {
            draw_flag=true;
            g_rect=Rect(x,y,0,0);
            showhelptext(event);
        }
        break;

        case EVENT_LBUTTONUP:
        {
            draw_flag=false;
            if(g_rect.width<0)
            {
                g_rect.x-=g_rect.width;
                g_rect.width*-1;
            }
            if(g_rect.height<0)
            {
                g_rect.y-=g_rect.height;
                g_rect.height*=-1;
            }
            //调整矩形范围
            draw_rect(img,g_rect);
            //确定矩形绘制 
            cout<<"矩形框的宽度＝"<<g_rect.width<<"，"<<"矩形框的高度＝"<<g_rect.height<<endl;
            Mat roi=dst(Range(g_rect.y,g_rect.y+g_rect.height),Range(g_rect.x,g_rect.x+g_rect.width));
            char name[10];
            i++;
            sprintf(name,"hjy_%d.png",i);
            imwrite(name,roi);   
            showhelptext(event);       
        }
        break;
    }
}

void draw_rect(Mat& img,Rect box)
{
    rectangle(img,box.tl(),box.br(),Scalar(g.uniform(0,255),g.uniform(0,255),g.uniform(0,255)),2);
}

void showhelptext(int event)
{
    switch(event)
    {
        case EVENT_LBUTTONUP:
        cout<<"两点已确定，进行矩形绘制"<<endl;
        break;
        case EVENT_LBUTTONDOWN:
        cout<<"已确定一点，请移动鼠标，绘制矩形"<<endl;
        break;
    }
}