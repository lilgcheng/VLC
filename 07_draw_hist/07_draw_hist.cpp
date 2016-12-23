#include <cstdio>
#include <opencv2/opencv.hpp>
using namespace cv;

void drawHistImg(const Mat &src, Mat &dst);

int main(){
    Mat src = imread("ig31.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    int histSize = 1080;
    float range[] = {0, 255} ;
    const float* histRange = {range};
    Mat histImg;
    calcHist(&src, 1, 0, Mat(), histImg, 1, &histSize, &histRange);

    Mat showHistImg(256,256,CV_8UC1,Scalar(255));  //把直方圖秀在一個256*256大的影像上
    drawHistImg(histImg, showHistImg);
    imshow("window1", src);
    imshow("window2", showHistImg);
    waitKey(0);

    return 0;
}

void drawHistImg(const Mat &src, Mat &dst){
    int histSize = 256;
    float histMaxValue = 0;
    for(int i=0; i<histSize; i++){
        float tempValue = src.at<float>(i);
        if(histMaxValue < tempValue){
            histMaxValue = tempValue;
        }
    }

    float scale = (0.9*256)/histMaxValue;
    for(int i=0; i<histSize; i++){
        int intensity = static_cast<int>(src.at<float>(i)*scale);
        line(dst,Point(i,255),Point(i,255-intensity),Scalar(0));
    }
}