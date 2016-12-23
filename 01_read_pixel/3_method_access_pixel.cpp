/**
 * 2016/15/15
 * project name: 3_method_access_pixel.cpp
 * Author : Oopscheng
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;


  
int main()  
{  
	//原始图像初始化  
	Mat image(240, 320, CV_8UC3, Scalar(0, 0, 0));  
	imshow("原始图像", image);  
  
	  
	//------------------指针操作-------------------------  
	double start = static_cast<double>(getTickCount());  
  
	int rowNumber = image.rows;//行数  
	int colNumber = image.cols * image.channels();//每一行元素个数 = 列数 x 通道数  
	for (int i = 0; i < rowNumber; i++)//行循环  
	{  
		uchar* data = image.ptr<uchar>(i);//获取第i行的首地址  
		for (int j = 0; j < colNumber; j++)//列循环  
		{  
			//开始处理  
			data[j] = 255;  
		}  
	}  
  
	double end = static_cast<double>(getTickCount());  
	double time = (end - start) / getTickFrequency();  
	cout << "指针操作运行时间为：" << time << "秒" << endl;  
	imshow("指针操作", image);  
	//---------------------------------------------------  
  
	//-----------------迭代器操作------------------------  
	start = static_cast<double>(getTickCount());  
  
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();//初始位置的迭代器  
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();//终止位置的迭代器  
	for (; it != itend; it++)  
	{  
		//处理BGR三个通道  
		(*it)[0] = 255;//B  
		(*it)[1] = 255;//G  
		(*it)[2] = 0;//R  
	}  
  
	end = static_cast<double>(getTickCount());  
	time = (end - start) / getTickFrequency();//计算时间  
	cout << "迭代器操作运行时间为：" << time << "秒" << endl;  
	imshow("迭代器操作", image);  
	//---------------------------------------------------  
  
	//----------------动态地址计算-----------------------  
	start = static_cast<double>(getTickCount());  
  
	rowNumber = image.rows;  
	colNumber = image.cols;  
	for (int i = 0; i < rowNumber; i++)  
		for (int j = 0; j < colNumber; j++)  
		{  
			//处理BGR三个通道  
			image.at<Vec3b>(i, j)[0] = 0;//B  
			image.at<Vec3b>(i, j)[1] = 255;//G  
			image.at<Vec3b>(i, j)[2] = 0;//R  
		}  
  
	end = static_cast<double>(getTickCount());  
	time = (end - start) / getTickFrequency();//计算时间  
	cout << "动态地址操作运行时间为：" << time << "秒" << endl;  
	imshow("动态地址操作", image);  
	//---------------------------------------------------  
  
	cvWaitKey(0);  
	return 1;  
  
}  
