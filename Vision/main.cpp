#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <list>
#include "floatfann.h"
#include "wiringSerial.h"
#include <string>

using namespace std;
using namespace cv;

char key;
Mat frame;
bool firstFrame = true;
bool oilRigInFirstFrame = false;
bool oilRigInSecondFrame = false;
Vec3b colores [10];

int sMax = 255, vMax = 56, hMax = 180;
int sMin = 0, vMin = 0, hMin = 20;

bool gui = false;

int handle;

struct Features
{
	 float M00,
	 M01,
	 M10,
	 M11,
	 M02,
	 M20,
	 F1,
	 F2,
	 Cx,
	 Cy;
};

enum Figure{
    NONE,
    OIL_RIG,
    TRIANGLE,
    CIRCLE,
    RECTANGLE
};

enum COMMANDS{
	ACK,
  	GET_FIGURE,
  	GET_OIL_RIG,
    GET_CIRCLE,
    GET_RECTANGLE,
    GET_TRIANGLE,
    GET_POS
};

int a,b,c,d,e = 0;

fann_type *result;
fann_type input[2];
struct fann *ann;


// Gets the HSV value of the clicked pixel
void mouseCallback(int event, int x, int y, int flags, void* param)
{
	int H,S,V;
    switch (event)
    {
        case CV_EVENT_LBUTTONDOWN:
            if(frame.data)
            {
                H = frame.at<Vec3b>(y,x).val[0];
                S = frame.at<Vec3b>(y,x).val[1];
                V = frame.at<Vec3b>(y,x).val[2];
                printf("H: %d, S: %d, V: %d\n",H,S,V);
            }
             
            break;
    }
}
// Get a random RGB color
Vec3b getRandomColor()
{
    return Vec3b(rand()%255,rand()%255,rand()%255);
}

// Fills all the pixels connected to the starting poing and paints the result on the output Mat
Features fillRegion(Mat &src, Mat &dst, Point start, Vec3b color)
{
    list<Point> cadena;									// Queue where pixels are going to be added
    Features features;									// Struct for saving all the calculated values
    features.M00 = features. M10 = features.M01 = 0;	// Initialize all values on 0 
    features.M20 = features.M02 = features.M11 = 0;		//
    cadena.push_back(start);							// Add the starting point to the Queue


    // Loop trough all the values of the queue
    while(!cadena.empty())  
    {
    	// Pop the top element and get its neighbourgs
        Point current = cadena.front();
        cadena.pop_front();
        Point top,bot,right,left;
        top = bot = right = left = current;
        top.y -= 1;
        bot.y += 1;
        right.x += 1;
        left.x -= 1;

        // Update the shape calculations
        features.M00++;
        features.M10 += current.x;
        features.M01 += current.y;
        features.M20 += current.x * current.x;
        features.M02 += current.y * current.y;
        features.M11 += current.y * current.x;

        // If the point exists and its value isn't zero, add it to the queue for processing
        if(top.y >= 0 && dst.at<Vec3b>(top) == Vec3b(0,0,0) && src.at<uchar>(top)!= 0)
        {
            dst.at<Vec3b>(top) = color;
            cadena.push_back(top);
        }

        if(bot.y < src.rows && dst.at<Vec3b>(bot) == Vec3b(0,0,0) && src.at<uchar>(bot)!= 0)
        {
            dst.at<Vec3b>(bot) = color;
            cadena.push_back(bot);
        }

        if(right.x < src.cols && dst.at<Vec3b>(right) == Vec3b(0,0,0) && src.at<uchar>(right)!= 0)
        {
            dst.at<Vec3b>(right) = color;
            cadena.push_back(right);
        }

        if(left.x >= 0 && dst.at<Vec3b>(left) == Vec3b(0,0,0) && src.at<uchar>(left)!= 0)
        {
            dst.at<Vec3b>(left) = color;
            cadena.push_back(left);
        }
    }

    // Finish the calculations on the shape
    features.Cx = features.M10 / features.M00;
    features.Cy = features.M01/ features.M00;
    float MU20 = features.M20 - (features.Cx*features.M10);
    float MU02 = features.M02 - (features.Cy*features.M01);
    float MU11 = features.M11 - (features.Cx*features.Cy*features.M00);
    float M00_2 = (features.M00*features.M00);
    float N20 = MU20/M00_2;
    float N02 = MU02/M00_2;
    float N11 = MU11/M00_2;
    float rad = atan2(2*MU11,MU20-MU02)/2;
    features.F1 = N20 + N02;
    features.F2 = ((N20 - N02)*(N20 - N02)) + (4*(N11*N11));
    return features;
}

// Iterates through the image and returns the biggest Shape found
// Returns True if any shape is found, False otherwise
bool getShapes(Mat &img, Mat &out, Features &result, int MinSize = 2000)
{
	short nRows = img.rows;
	short nCols = img.cols;
	int row,col;
	bool found = false;
	Features topShape;

	// Iterate all elements to find shapes in the image
	for ( row = 0; row < nRows; row++)
	{
		for( col = 0; col < nCols; col++)
		{
			Point p(col,row);
			// Look at the point only if theres a value on it and we haven't been there before
			if( img.at<uchar>(row,col) != 0 && out.at<Vec3b>(row,col) == Vec3b(0,0,0) )
			{
				Features f = fillRegion(img, out, p, colores[col%10]);
                if(topShape.M00 == 0 || f.M00 > topShape.M00)
                {
		    		found = true;
                    topShape = f;
                }
			}
		}
	}

	result = topShape;
	return found;
}



void on_trackbar(int, void*){

}

void fillCollors(){
    for(int i=0; i < 10; i++){
        colores[i] = getRandomColor();
    }
}

void initFannFIle(ofstream &file){
    file.open("trainingData.data");
    //file << "0 2 5"<< endl;
}

void printToFannFile(ofstream &file, Features feature, Figure figure){
        file << feature.F1 << " " << feature.F2 << endl;
        switch(figure){
            case NONE:
                file << "1 0 0 0 0";
                break;
            case OIL_RIG:
                file << "0 1 0 0 0";
                break;
            case TRIANGLE:
                file << "0 0 1 0 0";
                break;
            case CIRCLE:
                file << "0 0 0 1 0";
                break;
            case RECTANGLE:
                file << "0 0 0 0 1";
                break;
        }
        file << endl;
}

Figure detectShape(const Features &feature)
{
    input[0] = feature.F1;
    input[1] = feature.F2;
    result = fann_run(ann, input);
    int max = result[0];
    for(int i = 0; i < 5; i++)
        cout<< result[i]<< " ";
    cout << endl;
    for(int i = 1; i < 5; i++)
    {
        if(result[i] > result[max])
            max = i;
    }
    /*
    switch(max)
    {
        case 0:
            return NONE;
            break;
        case 1:
            return OIL_RIG;
            break;
        case 2:
            return TRIANGLE;
            break;
        case 3:
            return CIRCLE;
            break;
        case 4:
            return RECTANGLE;
            break;
        default:
            return NONE;
            break;
    }
    */
    
    switch(max)
    {
        case 0:
            cout << "NONE detectado" << endl;
            break;
        case 1:
            cout << "OIL_RIG detectado" << endl;
            break;
        case 2:
            cout << "TRIANGLE detectado" << endl;
            break;
        case 3:
            cout << "CIRCLE detectado" << endl;
            break;
        case 4:
            cout << "RECTANGLE detectado" << endl;
            break;
        default:
            break;
    }
    
}

bool findFigure(Figure figure, Mat frame)
{
    Mat threshold(240,320,CV_8UC1,255);
    inRange(frame,Scalar(hMin,sMin,vMin), Scalar(hMax,sMax,vMax), threshold);
    dilate(threshold, threshold, Mat());
    erode(threshold, threshold, Mat());
    Mat out( 240, 320, CV_8UC3, Scalar(0,0,0));
    Features shape;
    bool found = getShapes(threshold, out, shape);
    if(gui){
        imshow("Threshold", threshold);
        imshow("Segment", out);   // Show image frames on created window
        imshow("Original", frame);
        cvWaitKey(10);
    }
    out.refcount = 0;
    out.release();
    threshold.refcount = 0;
    threshold.release();
    return found && detectShape(shape) == figure;
}

int main(int argc, char *argv[])
{
	if(argc>1){
		if(String(argv[1]) == "-x")
		{
			gui = true;
            cout << "Starting process with GUI" << endl;
		}
	}

	handle = serialOpen("/dev/ttyAMA0",9600);
	if(handle == -1){
		cout << "Error opening SerialPort" << endl;
		return 1;
	}
	int datac = 0;



    ann = fann_create_from_file("robotics.net");
    if(gui){
        cout << "Creando pantallas" << endl;
	    cvNamedWindow("Original", 1);    //Create window
	    cvNamedWindow("Threshold", 1);
	    cvNamedWindow("Segment", 1);
	    createTrackbar("H min", "Segment", &hMin, 180, on_trackbar);
	    createTrackbar("H Max", "Segment", &hMax, 180, on_trackbar);
	    createTrackbar("S Min", "Segment", &sMin, 255, on_trackbar);
	    createTrackbar("S Max", "Segment", &sMax, 255, on_trackbar);
	    createTrackbar("V Min", "Segment", &vMin, 255, on_trackbar);
	    createTrackbar("V Max", "Segment", &vMax, 255, on_trackbar);

		//setMouseCallback("Original", mouseCallback);
	}

	VideoCapture camera(0);

    camera.set(CV_CAP_PROP_FRAME_WIDTH,320);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,240);

    if(!camera.isOpened()){
		cerr << "ERROR: Could not open camera" << endl;
		return 1;
	}

    fillCollors();
	int oilRigFound;
    Features shape;
    Features firstShape;

    ofstream fannFile;
    initFannFIle(fannFile);
/*
    while(1){
        cout << "Input Command" <<endl;
        char c;
        cin.get(c);
        camera >> frame;
        camera >> frame;
        camera >> frame;
        camera >> frame;
        camera >> frame;
        camera >> frame;
        switch(c){
            case 'o':
                cout<<"GET_OIL_RIG received"<< endl;
                if(findFigure(OIL_RIG, frame)){
                    cout << "OIL_RIG found, responding Arduino" << endl;
                    serialPutchar(handle,1);
                }else{
                    cout << "OIL_RIG not found, responding Arduino" <<endl;
                    serialPutchar(handle,0);
                }
                break;
            case 'c':
                cout<<"GET_CIRCLE received"<< endl;
                if(findFigure(CIRCLE, frame)){
                    cout << "CIRCLE found, responding Arduino" << endl;
                    //serialPutchar(handle,1);
                }else{
                    cout << "CIRCLE not found, responding Arduino" <<endl;
                    //serialPutchar(handle,0);
                }
                break;
            default:
                printf("Uknown command received: %d\n",c);
                break;
        }
    }
*/
    if(argc > 2 && String(argv[2]) == "-l")
    while(1){ 
        // Create infinte loop for live streaming
        Mat threshold(240,320,CV_8UC1,255);
        camera >> frame;
        cvtColor(frame, frame, CV_RGB2HSV);
        inRange(frame,Scalar(hMin,sMin,vMin), Scalar(hMax,sMax,vMax), threshold);
        dilate(threshold, threshold, Mat());
        erode(threshold, threshold, Mat());
        Mat out( 240, 320, CV_8UC3, Scalar(0,0,0));
        bool found = getShapes(threshold, out, shape);
        oilRigFound = findFigure(OIL_RIG, frame);
        key = cvWaitKey(10);     // Capture Keyboard stroke

        switch(char(key)){
            case 'i':
                if(firstFrame){
                    oilRigInFirstFrame = oilRigFound;
                    firstFrame = false;
                }else{
                    oilRigInSecondFrame = oilRigFound;
                    firstFrame = true;

                    if(oilRigInFirstFrame && !oilRigInSecondFrame)
                    {
                        cout << "OilRig 1 prendido" << endl;
                    }else if(oilRigInFirstFrame && oilRigInSecondFrame){
                        cout << "OilRig 2 prendido" << endl;
                    }else if(!oilRigInFirstFrame && oilRigInSecondFrame){
                        cout << "OilRig 3 prendido" << endl;
                    }else{
                        cout << "Error de lectura" << endl;
                    }
                }

                break;
            case 'q':
                printf("M00: %f F1: %f F2: %f Cx: %f Cy: %f\n",firstShape.M00, firstShape.F1, firstShape.F2, firstShape.Cx, firstShape.Cy);
                break;
            case 'n':
                printToFannFile(fannFile, firstShape, NONE);
                a++;
                printf("%d NONE recorded\n",a);
                break;
            case 'o':
                printToFannFile(fannFile, firstShape, OIL_RIG);
                b++;
                printf("%d OIL_RIG recorded\n",b);
                break;
            case 't':
                printToFannFile(fannFile, firstShape, TRIANGLE);
                c++;
                printf("%d TRIANGLE recorded\n",c);
                break;
            case 'r':
                printToFannFile(fannFile, firstShape, RECTANGLE);
                d++;
                printf("%d RECTANGLE recorded\n",d);
                break;
            case 'c':
                printToFannFile(fannFile, firstShape, CIRCLE);
                e++;
                printf("%d CIRCLE recorded\n",e);
                break;
                case 'e':
                    fannFile.close();
            default:
                break;
        }

        if (char(key) == 27){
            break;      // If you hit ESC key loop will break.
        }

        out.refcount = 0;
        out.release();
    }

	while(1){
		datac = serialDataAvail(handle);
		if(datac>0){
            camera >> frame;
            camera >> frame;
            camera >> frame;
            camera >> frame;
            camera >> frame;
            camera >> frame;
			int c = serialGetchar(handle);
            Features ft;
            Mat out( 240, 320, CV_8UC3, Scalar(0,0,0));
            Mat threshold(240,320,CV_8UC1,255);
			switch(c){
				case ACK:
					cout << "Acknowledge received" <<endl;
					break;
				case GET_OIL_RIG:
					cout<<"GET_OIL_RIG received"<< endl;
					if(findFigure(OIL_RIG, frame)){
						cout << "OIL_RIG found" << endl;
						serialPutchar(handle,1);
					}else{
						cout << "OIL_RIG not found" <<endl;
						serialPutchar(handle,0);
					}
					break;
                case GET_CIRCLE:
                    cout<<"GET_CIRCLE received"<< endl;
                    if(findFigure(CIRCLE, frame)){
                        cout << "CIRCLE found" << endl;
                        serialPutchar(handle,1);
                    }else{
                        cout << "CIRCLE not found" <<endl;
                        serialPutchar(handle,0);
                    }
                    break;

                case GET_RECTANGLE:
                    cout<<"GET_RECTANGLE received"<< endl;
                    if(findFigure(RECTANGLE, frame)){
                        cout << "RECTANGLE found" << endl;
                        serialPutchar(handle,1);
                    }else{
                        cout << "RECTANGLE not found" <<endl;
                        serialPutchar(handle,0);
                    }
                    break;

                case GET_TRIANGLE:
                    cout<<"GET_TRIANGLE received"<< endl;
                    if(findFigure(TRIANGLE, frame)){
                        cout << "TRIANGLE found" << endl;
                        serialPutchar(handle,1);
                    }else{
                        cout << "TRIANGLE not found" <<endl;
                        serialPutchar(handle,0);
                    }
                    break;
                case GET_POS:
                    cout << "GET_POS received" << endl;
                    
                    inRange(frame,Scalar(hMin,sMin,vMin), Scalar(hMax,sMax,vMax), threshold);
                    dilate(threshold, threshold, Mat());
                    erode(threshold, threshold, Mat());
                    getShapes(threshold, out, ft);
                    if(gui){
                        circle(out,Point(ft.Cx,ft.Cy),5,Scalar(0, 0, 255),-1);
                        imshow("Threshold", threshold);
                        imshow("Segment", out);   // Show image frames on created window
                        imshow("Original", frame);
                        cvWaitKey(10);
                    }
                    printf("%f %f %f %f %f\n",ft.M00, ft.M10, ft.M01, ft.Cx, ft.Cy );
                    break;

				default:
					do{
						printf("%c", c);
						datac--;
						c = serialGetchar(handle);
					}while(datac>0);
					break;
			}
            cout << "----------------------------------------" <<endl;
		}
	}


    


    return 0;
}
