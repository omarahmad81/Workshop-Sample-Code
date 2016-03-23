///Builds: 	g++ Src/BasicDisplay.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`  -o Output/BasicDisplay
///Runs: 	Output/./BasicDisplay 

/***********************************************************************************
 * 1. Open a camera stream or a video file (.AVI) or an image for processing.
 * 2. Get frames from the video
 * 3. Preprocess the frame to get a grayscale image with good shape segmentation
 * 
 * Author: 	Omar Ahmad
 * Date: 	20-03-2016
 * revised: 20-03-2016
 * 
 * ********************************************************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	Mat crnt_img, temp;
	int key;
	
	temp = imread("Data/BlobTest.jpg");
		
	crnt_img = temp.clone();
		
	imshow("Video",crnt_img);
	
	waitKey(0);
	
	cout << endl << "Exiting on user request" << endl;
	return 0;
}
