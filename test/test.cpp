#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, char **argv){
 Mat image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
 Mat imagegray = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE );//always convert image to the grayscale

 namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE 
 // namedWindow("imagegray",CV_WINDOW_NORMAL);//Custom sizes
 imshow("image",image);
 // imshow("imagegray",imagegray);
 // resizeWindow("imagegray",640,480);
 waitKey(0);
 return 0;
}
