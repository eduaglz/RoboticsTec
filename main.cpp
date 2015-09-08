#include <iostream>
#include <cv.h>
#include <highgui.h>
 
using namespace std;
using namespace cv;
char key;
int main()
{
    cvNamedWindow("Camera_Output", 1);    //Create window
    VideoCapture camera(0);
    camera.set(CV_CAP_PROP_FRAME_WIDTH,320);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,240);
     if(!camera.isOpened())
      {
        cerr << "ERROR: Could not open camera" << endl;
        return 1;
      }
    while(1){ //Create infinte loop for live streaming
        Mat frame;
	Mat threshold(320,240,CV_8U);
        camera >> frame;
        cvtColor(frame, frame, CV_RGB2HSV);
	threshold(frame, frame, Scalar(0,0,0), Scalar(255,255,50), threshold);
	imshow("Camera_Output", threshold);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
    return 0;
}
