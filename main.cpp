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
     if(!camera.isOpened())
      {
        cerr << "ERROR: Could not open camera" << endl;
        return 1;
      }
    while(1){ //Create infinte loop for live streaming
        Mat frame;
        camera >> frame;
        imshow("Camera_Output", frame);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
    return 0;
}