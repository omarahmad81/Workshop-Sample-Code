///Builds: 	g++ Src/BlobDetection.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`  -o Output/blob_detection
///Runs: 	Output/./blob_detection 

/***********************************************************************************
 * 1. Open a video file (.AVI) or an image for processing.
 * 2. Get frames from the video
 * 3. Preprocess the frame to get a grayscale image with good shape segmentation
 *    for the moving particle
 * 4. Use a object recognition algo e.g. SimpleBlobDetector to locate the particle
 * 5. Then you can track it on a frame to frame basis
 * 
 * 
 * Author: 	Omar Ahmad
 * Date: 	29-04-2015
 * revised: 29-04-2015
 * 
 * ********************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

//#define USE_VIDEO
#define USE_CUSTOM_PARAMS

//#define TRESHOLD

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	int key;
	Mat temp, crnt_img, crnt_img_gray, result;
	
	#ifdef USE_VIDEO
		VideoCapture cap;		// video capture object	

		cap.open("Data/UltraSound/BubbleCut200.avi"); // open the video file 
		
		if(!cap.isOpened())  // check if we succeeded
		{
			cout<<"Cannot open video file: " << argv[1] << endl;
			exit(1);
		}
		cap >> temp;					// get frames
		
		crnt_img = temp.clone();
	#else
	//crnt_img = imread("Data/UltraSound/blob.png", IMREAD_GRAYSCALE);	
	crnt_img = imread("Data/UltraSound/BlobTest.jpg");	
	
	#endif
	
	namedWindow("Video", WINDOW_AUTOSIZE );
	cvMoveWindow("Video", 850, 50);
	
	//namedWindow("BlobDetected", WINDOW_AUTOSIZE );
	//cvMoveWindow("BlobDetected", 850, 850);
	
	/****************** Setup the blob detector ***********************/
		
		#ifdef USE_CUSTOM_PARAMS
			// Setup SimpleBlobDetector parameters.
			SimpleBlobDetector::Params params;
			 
			// Change thresholds
			params.minThreshold = 80;
			params.maxThreshold = 255;
			 
			// Filter by Area.
			params.filterByArea = true;
			params.minArea = 300;
			params.maxArea = 9000;
			// Filter by Circularity
			params.filterByCircularity = true;
			params.minCircularity = 0.9;
			 
			// Filter by Convexity
			params.filterByConvexity = true;
			params.minConvexity = 0.7;
			 
			// Filter by Inertia
			params.filterByInertia = true;
			params.minInertiaRatio = 0.7;
		
		// Set up detector with params
		SimpleBlobDetector detector(params);
		
		#else
			// Set up the detector with default parameters.
			SimpleBlobDetector detector;
		#endif
	
		std::vector<KeyPoint> keypoints; 
	/******************************************************************/
	
	
	
	#ifdef USE_VIDEO 
	while(1)
	{
		if (crnt_img.empty())
		{
			cout << " < < < End of file! > > > "<< endl << endl;
			cap.release();	// close video file here
			break;
		}
	#endif

	
		/****************** Perform Preprocessing here ****************/
		Mat pre_processed_img;
		cvtColor(crnt_img, pre_processed_img, CV_RGB2GRAY);		
		
		/// Threshold here to capture only significant movements
		#ifdef TRESHOLD
		adaptiveThreshold(pre_processed_img,pre_processed_img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -3);
		imshow("Threshold", pre_processed_img);
		#endif
		/**************************************************************/
	
		detector.detect( pre_processed_img, keypoints);
		//detector.detect( crnt_img, keypoints);
		
		// Draw detected blobs as red circles.
		// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
		drawKeypoints( pre_processed_img, keypoints, result, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
		
		imshow("BlobDetected", result);
		imshow("Video",crnt_img);
		
		
		key = (unsigned char)waitKey(0);
	
	
	
	#ifdef USE_VIDEO
		if(key == 27)
		break;
	
		cap >> temp;					// get frames
	
		crnt_img = temp.clone();
	
	
	
	}
	#endif
	
	cout << endl << "Exiting on user request" << endl;
}
