/*
#include<iostream>
#include<cstring>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void)
{
    printf("opencv version"CV_VERSION);
    Mat src=imread("test.jpeg",4|2);//无损读入图片
    imshow("beauty",src);
    waitKey(0);
    return 0;
}//输出：30
*/

/*
#include<iostream>
#include <string> // string, sprintf
#include <cstring> // strlen(linux)
using namespace std;
 
int main() {
	int n = 100;
	char ch[10];
	sprintf(ch, "%d", n);
 
	//下面把char*转成string
	string str(ch, ch + strlen(ch));
 
	printf("%s\n",str.c_str());
 
	return 0;
}
*/

//格式化输出
#include<iostream>
#include<cstring>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat M(4,2,CV_8UC1,Scalar::all(1));//如果3通道，说明一列有３个子列，所以有４行，６列
	cout<<"M="<<format(M,Formatter::FMT_C)<<endl;
	cout<<"M="<<format(M,Formatter::FMT_CSV)<<endl;
	cout<<"M="<<format(M,Formatter::FMT_DEFAULT)<<endl;
	cout<<"M="<<format(M,Formatter::FMT_MATLAB)<<endl;
	//最清晰
	cout<<"M="<<format(M,Formatter::FMT_NUMPY)<<endl;
	cout<<"M="<<format(M,Formatter::FMT_PYTHON)<<endl;
	//这个也还行
	

	Mat a(M);//拷贝构造函数
	Mat b=M;//赋值

	Mat c=M.clone();
	Mat d;
	M.copyTo(d);
	cout<<"d="<<format(d,Formatter::FMT_MATLAB)<<endl;

	cout<<"修改其中个别元素"<<endl;
	a.ptr<uchar>(0)[0]=12;
	a.ptr<uchar>(0)[1]=32;
	cout<<"a="<<format(a,Formatter::FMT_MATLAB)<<endl;
	cout<<"b="<<format(b,Formatter::FMT_MATLAB)<<endl;
	cout<<"M="<<format(M,Formatter::FMT_MATLAB)<<endl;
	//改a，Ｍ也会跟着变，但是d不会变因为两者内存空间已经不同，互不干扰
	cout<<"c="<<format(c,Formatter::FMT_MATLAB)<<endl;
	cout<<"d="<<format(d,Formatter::FMT_MATLAB)<<endl;


	cout<<"改变矩阵尺寸"<<endl;
	b.create(4,1,CV_8UC1);
	//没有超出原先的尺寸，不需要重新分配内存空间
	//这里怎么也重新分配呢存空间了？？？？好像只要尺寸变了就要重新分配内存了
	d.create(2,4,CV_8UC1);
	a.create(1,8,CV_8UC1);
	cout<<"b="<<format(b,Formatter::FMT_MATLAB)<<endl;
	cout<<"a="<<format(a,Formatter::FMT_MATLAB)<<endl;
	cout<<"M="<<format(M,Formatter::FMT_MATLAB)<<endl;
	cout<<"d="<<format(d,Formatter::FMT_MATLAB)<<endl;


	Mat z(4,4,CV_8UC2);
	randu(z,Scalar(0,1),Scalar(255,10));
	//随机填充，第二三个参数是最小最大值
	cout<<"z="<<format(z,Formatter::FMT_PYTHON)<<endl;

	return 0;
}


