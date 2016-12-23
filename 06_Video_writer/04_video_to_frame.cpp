#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cv.h>
#include <string>
#include <sstream>
using namespace cv;
using namespace std;
int c=0;
string int2str(int &);

int main(int argc, char **argv){
	string s;

	VideoCapture cap("VideoTest.avi"); // open the video file for reading

	if ( !cap.isOpened() )  // if not success, exit program
	{
		 cout << "Cannot open the video file" << endl;
		 return -1;
	}

	//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

	cout << "Frame per seconds : " << fps << endl;

	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	namedWindow("MyVideo_gray",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	while(1)
	{
		Mat frame;
		Mat Gray_frame;
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}
		cvtColor(frame, Gray_frame, CV_BGR2GRAY);
		s = int2str(c);
		//cout<<("%d\n",frame )<<endl;
		c++;
		imshow("MyVideo", frame); //show the frame in "MyVideo" window
		imshow("MyVideo_gray", Gray_frame);
		imwrite( "ig"+s+".jpg", Gray_frame );
		if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
				cout << "esc key is pressed by user" << endl; 
				break; 
		}
	}

	return 0;

}

//int to string function
string int2str(int &i) {
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}
