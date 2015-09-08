#include <iostream>
#include <cv.h>
#include <highgui.h>
 
using namespace std;
using namespace cv;
char key;
int main()
{
    cvNamedWindow("Original", 1);    //Create window
    cvNamedWindow("Threshold", 1);
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
	Mat threshold(320,240,CV_8UC1,255);
	camera >> frame;
	inRange(frame,Scalar(0,0,0), Scalar(255,255,20), threshold);
        //camera >> frame;
        cvtColor(frame, frame, CV_RGB2HSV);
	//threshold(frame, frame, Scalar(0,0,0), Scalar(255,255,50), threshold);
	imshow("Threshold", threshold);   //Show image frames on created window
        imshow("Original", frame);
	key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
    return 0;
}
