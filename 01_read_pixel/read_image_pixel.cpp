
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv){
	int c = 0;
	IplImage *src;
	src = cvLoadImage("lena.jpg",1);
	int width=src->width;//图片宽度
	int height = src->height;//图片高度

	for (size_t row=0;row<height;row++){
		uchar* ptr = (uchar*)src->imageData+row*src->width;//获得灰度值数据指针
		for (size_t cols=0;cols<width;cols++){
			int intensity=ptr[cols];
			cout<<" "<<intensity<<" ";
			c++;
		}
		cout<<"\n"<<endl;
	}
	printf("width(%d) x height(%d) = %d\n",width,height,c);
	cvSave("1R.jpg",src);         //使用cvSave將數值轉換，使用記事本打開可直接看pixel的灰階值(0~255)
	return 0;  
}
