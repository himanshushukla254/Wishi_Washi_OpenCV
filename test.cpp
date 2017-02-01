/******************Code for Wishi Washi Game**********************************/

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

Mat func(Mat frame2, Mat M);                   		        //function declaration
Mat frame1;					   	 	//frame1 declaration
int X, Y;							//variable declaration

// main starts here-----------------------------------
int main(int argc, char** argv)
{
	
	char key;
	
	VideoCapture cap;					//videocapture class
	if (!cap.open(0))					//check if we can use the  device or not
		return 0;
	X = cap.get(3);
	Y = cap.get(4);
	Mat M(Y, X, CV_8UC3, Scalar::all(0));                   
	Mat outputFrame, foutputFrame;
	Mat frame3;
	cap >> frame1;						//get frame1
	while (1)
	{
		Mat frame2;					//get frame2
		cap >> frame2;
		M = func(frame2, M);				//function call
		frame2.copyTo(outputFrame, M);  

		flip(outputFrame, foutputFrame, 1);             // flipping around y-axis
		key = cvWaitKey(1);
		if (char(key) == 27)					
			break;					//esc to terminate the program	
		frame2 = foutputFrame;
		imshow("Webcam", frame2);
	}
	
	return 0;
}

Mat func(Mat frame2, Mat M)
{
	Mat diff;
	absdiff(frame1, frame2, diff);				//return differences
	float pixelsc;
	
	//USE THRESHOLD and MASK functions to optimize -- This is what the function actually does
	float threshold = 150;
	for (int x = 1; x < X; x++)
	{
		for (int y = 1; y < Y; y++)
		{
			Vec3b pixel = diff.at<Vec3b>(y, x);
			pixelsc = sqrt(pixel[0] * pixel[0] + pixel[1] * pixel[1] + pixel[2] * pixel[2]);	//net intensity after diff
			if (pixelsc>threshold)
			{
				//make pixel visible
				M.at<Vec3b>(y, x)[0] = 255;
				M.at<Vec3b>(y, x)[1] = 255;
				M.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}
	frame1 = frame2;
	return M;
}
