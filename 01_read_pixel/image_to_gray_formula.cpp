/**
 * 2016/15/15
 * project name:image_to_gray_formula.cpp
 * Author : Oopscheng
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;
double START,END;
Mat Togray(Mat &image, int cols,int rows); 
int main( int argc, char** argv ){
	START = clock();
	Mat image;
	image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	int cols=image.cols;//length
	int rows=image.rows;//width
	printf("width(i)=%d\n",cols);
	printf("hight(j)=%d\n",rows);
	namedWindow( "gray_image", CV_WINDOW_AUTOSIZE );
	imshow( "gray_image", Togray(image,cols,rows));
	namedWindow( "Lena", CV_WINDOW_AUTOSIZE );
	imshow( "Lena", image);
	END = clock();
	cout << (END - START) / CLOCKS_PER_SEC << endl;
	waitKey(0);
	return 0;
}

/**
 * [Togray description]
 * @param image [description]
 * @param cols  [height]
 * @param rows  [width]
 */
Mat Togray(Mat &image, int cols,int rows){
	int i,j;
	float b,g,r;
	float current_f;//作灰階運算得到正確值current_f
	int current_i=0;//作灰階運算其整數值Y
	int y=0;//四捨五入判斷current_f與Y值是否要進位
	Mat gray_image=Mat(rows,cols,CV_8UC1);//CV_8UC1 = 8bit Unsign integer channel 1
	for(i=0;i<cols;i++){
		for(j=0;j<rows;j++){
			b = image.at<Vec3b>(j, i)[0];//B read column
			g = image.at<Vec3b>(j, i)[1];//G
			r = image.at<Vec3b>(j, i)[2];//R
			current_f=0.299*r+0.587*g+0.114*b;
			current_i=0.299*r+0.587*g+0.114*b;
			if(current_f-current_i>=0.5){
				y=current_i+1;
			}else{
				y=current_i;
			}
			gray_image.at<unsigned char>(j,i)=current_i;
		 
			// printf("%f,%d\n",current_f,y);
	 		//printf("(i,j,y)=(%d,%d,%d),%f %f %f\n",i,j,y,b,g,r);//(0,0)~(255~255)
		}
	}
	return gray_image;
}