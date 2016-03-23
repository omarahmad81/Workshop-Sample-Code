///Builds: 	g++ Src/FaceDetect.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`  -o Output/FaceDetect
///Runs: 	Output/./FaceDetect 

#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <fstream>

#define USE_IMAGE
//#define USE_CAMERA

using namespace std;
using namespace cv;

int main(int argc, char** argv )
{
   

    VideoCapture VideoStream(0);

    if (!VideoStream.isOpened())
    {
        cout << "Error: Cannot open video stream from camera" << endl;
        return 1;
    }
    
    CascadeClassifier face_cascade;
    face_cascade.load("Data/haarcascades/haarcascade_frontalface_default.xml");
    CascadeClassifier eye_cascade;
    eye_cascade.load("Data/haarcascades/haarcascade_eye.xml");
    
    vector<Rect> Faces;
    vector<Rect> Eyes;

    Mat crnt_img;
    Mat gray_img;
    
    #ifdef USE_IMAGE
    crnt_img = imread("Data/criceters1.jpg", CV_LOAD_IMAGE_COLOR); 
    cvtColor(crnt_img, gray_img, COLOR_RGB2GRAY);
    
    face_cascade.detectMultiScale(gray_img, Faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        
        
        for (int i = 0; i < Faces.size(); i++)
        {
            rectangle(crnt_img, Faces[i], Scalar(0,255,0));
        }

    imshow("Face Detect", crnt_img);
	
	waitKey(0);
	#endif
	
	#ifdef USE_CAMERA
    while(true)
    {
        VideoStream >> crnt_img;
        cvtColor(crnt_img, gray_img, COLOR_RGB2GRAY);
        
        face_cascade.detectMultiScale(gray_img, Faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        
        
        for (int i = 0; i < Faces.size(); i++)
        {
            rectangle(crnt_img, Faces[i], Scalar(0,255,0));
        }

        imshow("Face Detect", crnt_img);

        if (waitKey(30) >= 0) break;
    }
	#endif

    return 0;
}
