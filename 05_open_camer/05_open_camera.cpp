/**
 * 2016/12/04
 * project name: 05_openc_camera.cpp
 * Author : Oopscheng
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){

	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout<<"Cannot open the web cam\n";
		return -1;
	}	
//cap.set(CV_CAP_PROP_FRAME_HEIGHT,320);//window height
//cap.set(CV_CAP_PROP_FRAME_WIDTH,240);//window  witdh

Mat frame;

while(1){

	bool bSuccess = cap.read(frame);
	imshow("frame", frame);
	if(waitKey(30) >= 0) 
		break;
}
	system("PAUSE");
	return 0;
}

