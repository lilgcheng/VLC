
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

int main(int argc, char **argv){
	Mat image = imread("ig31.jpg", CV_LOAD_IMAGE_COLOR);
	Mat imagegray = imread("ig31.jpg", CV_LOAD_IMAGE_GRAYSCALE );//always convert image to the grayscale
	printf("image.cols = %d\n",image.cols );
	printf("image.rows = %d\n",image.rows );
	int array[image.rows] = {0};
	for (int i = 0; i < 1080; i++){
		for (int j = 0; j < 1920; j++){
			int gray_value = (int)imagegray.at<uchar>(i,j);
			array[i] += gray_value;
				// printf("[%d] = %d\n",j,gray_value);
		}
		// printf("\n--------------------------------------------------------------------------------------------------------\n");
	}
	for (int i = 0; i < image.rows ; i++){		
		array[i] = array[i]/1920;
		printf("array[%d]=%3d\n",i,array[i]);
	}

	namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE 
	imshow("image",imagegray);
	waitKey(0);
	return 0;
}
