
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdio>
using namespace cv;
using namespace std;
void MyCallbackForBrightness(int iValueForBrightness, void *userData);
void MyCallbackForContrast(int iValueForContrast, void *userData);
Mat src1;
Mat src2;
int main(int argc, char** argv)
{
	// Read original image 
	src1 = imread("rain.jpg");
	src2 = imread("rain.jpg", CV_LOAD_IMAGE_GRAYSCALE);//always convert image to the grayscale)
	  //if fail to read the image
	if (src1.data == false) 
	{ 
		cout << "Error loading the image" << endl;
		return -1; 
	}

	// Create a window
	namedWindow("My Window", 1);

	int iValueForBrightness = 50;
	int iValueForContrast = 50;

	//Create track bar to change brightness
	createTrackbar("Brightness", "My Window", &iValueForBrightness, 100, MyCallbackForBrightness, &iValueForContrast);

	 //Create track bar to change contrast
	createTrackbar("Contrast", "My Window", &iValueForContrast, 100, MyCallbackForContrast, &iValueForBrightness);
  
	imshow("My Window", src1);
	imshow("My Gray", src2);
	 // Wait until user press some key
	waitKey(0);


	 return 0;
}

void MyCallbackForBrightness(int iValueForBrightness, void *userData)
{
	 Mat dst;
	 int iValueForContrast = *( static_cast<int*>(userData) );

	  //Calculating brightness and contrast value
	 int iBrightness = iValueForBrightness - 50;
	 double dContrast = iValueForContrast / 50.0;

	  //Calculated contrast and brightness value
	 cout << "MyCallbackForBrightness : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

	  //adjust the brightness and contrast
	 src1.convertTo(dst, -1, dContrast, iBrightness); 

	  //show the brightness and contrast adjusted image
	 imshow("My Window", dst);
}

void MyCallbackForContrast(int iValueForContrast, void *userData)
{
	 Mat dst;
	 int iValueForBrightness = *( static_cast<int*>(userData) );

	  //Calculating brightness and contrast value
	 int iBrightness = iValueForBrightness - 50;
	 double dContrast = iValueForContrast / 50.0;

	  //Calculated contrast and brightness value
	 cout << "MyCallbackForContrast : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

	  //adjust the brightness and contrast
	 src1.convertTo(dst, -1, dContrast, iBrightness); 

	  //show the brightness and contrast adjusted image
	 imshow("My Window", dst);
}