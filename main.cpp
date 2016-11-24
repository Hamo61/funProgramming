#include <iostream>
//#include <highgui.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <raspicam/raspicam_cv.h>

using namespace cv;
using namespace std;

int main()
{
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    raspicam::RaspiCam_Cv Camera;
    //Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 240 );
    //Camera.set( CV_CAP_PROP_FRAME_WIDTH, 320 );

    //Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 ); //schwarz weiß
    Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3);	//farbe

    //Open camera
    cout<<"Opening Camera..."<<endl;
    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}

    while (1)
    {
        Mat frame;

        //bool bSuccess = cap.read(frame); // read a new frame from video
	Camera.grab();
        Camera.retrieve (frame);
	//cvtColor(frame, frame, CV_BGR2RGB);
	cvtColor(frame, frame, CV_RGB2BGR);
	//cv::cvtColor(bgrMat, rgbMat, cv::COLOR_BGR2RGB);

        //if (!bSuccess) //if not success, break loop
       // {
       //      cout << "Cannot read a frame from video stream" << endl;
       //      break;
       // }

        imshow("MyVideo", frame); //show the frame in "MyVideo" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break;
       }
    }
    return 0;

}
