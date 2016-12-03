#define LAPTOP

#define CAMERA_WIDTH   640
#define CAMERA_HEIGHT  480

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>

#ifndef LAPTOP
#include <raspicam/raspicam_cv.h>
#endif

using namespace cv;
using namespace std;

// Functions
int initializeCamera();
int getFrame();
int getFps();

//global variables
Mat frame;
#ifndef LAPTOP
raspicam::RaspiCam_Cv Camera;
#else
VideoCapture camera(0);
#endif

int main()
{
	//Open camera
	cout<<"Opening Camera..."<<endl;
	initializeCamera();
   
	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
   
 
     
    while (1)
	{
        //getFrame();
		camera >> frame;
		imshow("MyVideo", frame); //show the frame in "MyVideo" window
		if (waitKey(1) == 27) //wait for 'esc' key press for 30ms. If 'esc' ke$
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}		
	}
	return 0;
}

/*
####################################################################
function to initialize the camera setup
####################################################################
*/
int initializeCamera()
{
#ifndef LAPTOP
	//raspicam::RaspiCam_Cv Camera; now global variable
	Camera.set( CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH );
	Camera.set( CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT );
	//Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 ); //schwarz weiß
	Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3);	//farbe
	if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}

#else
	//VideoCapture camera(0); // open the video camera no. 0 // now global variable

	if (!camera.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	camera.set(CV_CAP_PROP_FRAME_WIDTH,CAMERA_WIDTH);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT,CAMERA_HEIGHT);

	//double dWidth = camera.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	//double dHeight = camera.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	//cout << "Frame size : " << dWidth << " x " << dHeight << endl;
#endif
	return 0;
}


/*
####################################################################
function to get a frame from the camera
####################################################################
*/
int getFrame()
{
#ifndef LAPTOP
	Camera.grab();
	Camera.retrieve (frame);
	cvtColor(frame, frame, CV_BGR2RGB);
	//cvtColor(frame, frame, CV_RGB2BGR);
	//cv::cvtColor(bgrMat, rgbMat, cv::COLOR_BGR2RGB);
#else
	bool bSuccess = camera.read(frame); // read a new frame from video
	if (!bSuccess) //if not success, break loop
	{
		cout << "Cannot read a frame from video stream" << endl;
		//break;
	}
#endif
	return 0;	
}

/*
####################################################################
function to get a frame from the camera
####################################################################
*/
int getFps()
{
    double fps;
    int num_frames = 300;
    time_t start, end;

	// Start time
    time(&start);

//	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    // Grab a few frames
    for(int i = 0; i < num_frames; i++)
    {
        //getFrame();
		camera >> frame;
//		imshow("MyVideo", frame); //show the frame in "MyVideo" window
//		if (waitKey(1) == 27) //wait for 'esc' key press for 30ms. If 'esc' ke$
//		{
//			cout << "esc key is pressed by user" << endl;
//			break;
//		}
    }

    // End Time
    time(&end);

	// Time elapsed
    double seconds = difftime (end, start);
    cout << "Time taken : " << seconds << " seconds" << endl;
    
    // Calculate frames per second
    fps  = num_frames / seconds;
    cout << "Estimated frames per second : " << fps << endl;

	return 0;
}
