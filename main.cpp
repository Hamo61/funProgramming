#define LAPTOP

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifndef LAPTOP
#include <raspicam/raspicam_cv.h>
#endif

using namespace cv;
using namespace std;

int main()
{
	//Open camera
	cout<<"Opening Camera..."<<endl;

#ifndef LAPTOP
	raspicam::RaspiCam_Cv Camera;
	//Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 240 );
	//Camera.set( CV_CAP_PROP_FRAME_WIDTH, 320 );
	//Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 ); //schwarz weiß
	Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3);	//farbe
	if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}

#else
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;
#endif
   
	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    
	Mat frame;

	while (1)
	{
		

#ifndef LAPTOP
		Camera.grab();
		Camera.retrieve (frame);
		cvtColor(frame, frame, CV_BGR2RGB);
		//cvtColor(frame, frame, CV_RGB2BGR);
		//cv::cvtColor(bgrMat, rgbMat, cv::COLOR_BGR2RGB);
#else
		bool bSuccess = cap.read(frame); // read a new frame from video
		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}
#endif
		imshow("MyVideo", frame); //show the frame in "MyVideo" window
		if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' ke$
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	cout << "A";
	}
	return 0;
}
