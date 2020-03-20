#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], -1);
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    Mat src_mat = imread(argv[1],1);
    Mat gray_mat;
    cvtColor(src_mat, gray_mat, CV_BGR2GRAY);
    namedWindow("原图", WINDOW_AUTOSIZE );
    imshow("原图", src_mat);
    imshow("灰度图", gray_mat);
    waitKey(0);
    return 0;
}
