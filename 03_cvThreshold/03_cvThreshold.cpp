
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdio>
#include <cv.h>
using namespace cv;
using namespace std;

void * WindowHandle1;

char FileName[]="rain.jpg";
char TrackbarName[]="Threshold";

int TrackbarInitValue=180;
int TrackbarStopValue=255;

IplImage *Image1;
IplImage *Image2;
CvSize Image2Size;

int main()
{
	char FileName[]="rain.jpg";
    IplImage *Image;    
    Image = cvLoadImage(FileName,CV_LOAD_IMAGE_GRAYSCALE);   // 讀取影像,轉換為灰階
    cvThreshold(Image,Image,128,255,CV_THRESH_BINARY);       // 將灰階值在128以上設為255,以下則設為0
    cvShowImage("Image",Image);
    cvWaitKey(0);
    cvDestroyWindow("Image");
    cvReleaseImage(&Image); 
    return 0;

}
