#include <iostream>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <list>
#include "floatfann.h"
 

using namespace std;
using namespace cv;
char key;
Mat frame;
bool firstFrame = true;
bool oilRigInFirstFrame = false;
bool oilRigInSecondFrame = false;
Vec3b colores [10];

int sMax = 255, vMax = 44, hMax = 180;
int sMin = 0, vMin = 0, hMin = 20;

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

enum Figures{
    NONE,
    OIL_RIG,
    TRIANGLE,
    CIRCLE,
    RECTANGLE
};

int a,b,c,d,e = 0;

fann_type *result;
fann_type input[2];
struct fann *ann;

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


/*        
			case CV_EVENT_MOUSEMOVE:
            if(frame.data) 
            {
                int Hm = frame.at<Vec3b>(y,x).val[0];
                int Sm = frame.at<Vec3b>(y,x).val[1];
                int Vm = frame.at<Vec3b>(y,x).val[2];
                mouseHSV[0] = Hm;
                mouseHSV[1] = Sm;
                mouseHSV[2] = Vm;
                printf("H: %d, S: %d, V: %d\n",Hm,Sm,Vm);
            }
            break;
*/
    }
}

Vec3b getRandomColor()
{
    return Vec3b(rand()%255,rand()%255,rand()%255);
}

Features fillRegion(Mat &src, Mat &dst, Point start, Vec3b color)
{
    int size = 0;
    list<Point> cadena;
    cadena.push_back(start);
    Features features;
    features.M00 = features. M10 = features.M01 = 0;
    features.M20 = features.M02 = features.M11 = 0;
    //cout << "Iniciando fillRegion" << endl;

    while(!cadena.empty())  
    {
    	//cout << "Tamaño de la cadena:" << cadena.size() << endl;
        if(cadena.size()>size)
        {
            size = cadena.size();
        }

        Point current = cadena.front();
        cadena.pop_front();
        Point top,bot,right,left;
        top = bot = right = left = current;
        top.y -= 1;
        bot.y += 1;
        right.x += 1;
        left.x -= 1;
        features.M00++;
        features.M10 += current.x;
        features.M01 += current.y;
        features.M20 += current.x * current.x;
        features.M02 += current.y * current.y;
        features.M11 += current.y * current.x;
        /*
        cout << "Current: " << current << endl;
 		cout << top << endl;
 		cout << bot << endl;
 		cout << right << endl;
 		cout << left << endl;
 		*/
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
    //cout << "Finishing fillRegion" << endl;
    return features;
}

list<Features> getShapes(Mat &img, Mat &out, int minSize = 2000)
{
	short nRows = img.rows;
	short nCols = img.cols;
	int row,col;
	bool found = false;
    list<Features> shapes;
	// printf("Creando mat temporal de %dx%d\n",nRows,nCols);
	// out = Mat(img.rows, img.cols, Scalar(0,0,0));
	// Iterate all elements to find shapes in the image
	for ( row = 0; row < nRows; row++)
	{
		// uchar *ptr = img.ptr<uchar>(row);
		for( col = 0; col < nCols; col++)
		{
			Point p(col,row);
			// cout << row << "," << col << endl;
			// Look at the point only if theres a value on it and we haven't been there before
			if( img.at<uchar>(row,col) != 0 && out.at<Vec3b>(row,col) == Vec3b(0,0,0) )
			{
				// printf("Punto encontrado en (%d,%d)\n",row,col);
				Features f = fillRegion(img, out, p, colores[shapes.size()%10]);
                if(f.M00 >= minSize)
                    shapes.push_back(f);
			}
		}
	}
    //cout << "Finishing getShapes" << endl;
	return shapes;
}

Figures detectShape(const Features &feature)
{
    input[0] = feature.F1;
    input[1] = feature.F2;
    result = fann_run(ann, input);
    int max = result[0];
    for(int i = 1; i < 5; i++)
    {
        if(result[i] > result[max])
            max = i;
    }

    //printf("%f %f %f %f %f\n",result[0],result[1],result[2],result[3],result[4]);
/*    
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
*/
    //printf("M00: %f F1: %f F2: %f Cx: %f Cy: %f\n",feature.M00, feature.F1, feature.F2, feature.Cx, feature.Cy);
    /*
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
    */


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

void printToFannFile(ofstream &file, Features feature, Figures figure){
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

int main()
{
    ann = fann_create_from_file("robotics.net");
    cvNamedWindow("Original", 1);    //Create window
    cvNamedWindow("Threshold", 1);
    cvNamedWindow("Segment", 1);
    createTrackbar("H min", "Segment", &hMin, 180, on_trackbar);
    createTrackbar("H Max", "Segment", &hMax, 180, on_trackbar);
    createTrackbar("S Min", "Segment", &sMin, 255, on_trackbar);
    createTrackbar("S Max", "Segment", &sMax, 255, on_trackbar);
    createTrackbar("V Min", "Segment", &vMin, 255, on_trackbar);
    createTrackbar("V Max", "Segment", &vMax, 255, on_trackbar);

setMouseCallback("Original", mouseCallback);

	VideoCapture camera(0);
    camera.set(CV_CAP_PROP_FRAME_WIDTH,320);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,240);

    if(!camera.isOpened()){
		cerr << "ERROR: Could not open camera" << endl;
		return 1;
	}
    fillCollors();
	int oilRigFound;
    list<Features> shapes;
    Features firstShape;

    ofstream fannFile;
    initFannFIle(fannFile);
    while(1){ 
    	// Create infinte loop for live streaming
	clock_t tStart = clock();
	Mat threshold(240,320,CV_8UC1,255);
	camera >> frame;
	cvtColor(frame, frame, CV_RGB2HSV);
	inRange(frame,Scalar(hMin,sMin,vMin), Scalar(hMax,sMax,vMax), threshold);
	//erode(threshold, threshold, Mat());
	dilate(threshold, threshold, Mat());
	erode(threshold, threshold, Mat());
        Mat out( 240, 320, CV_8UC3, Scalar(0,0,0));
        shapes = getShapes(threshold, out);
        while(!shapes.empty())
        {
            Features f = shapes.front();
            firstShape = f;
            oilRigFound |= detectShape(f) == OIL_RIG;
            shapes.pop_front();
        }

		//oilRigFound = getShapes(threshold, out);
		imshow("Threshold", threshold);
		imshow("Segment", out);   // Show image frames on created window
	    	imshow("Original", frame);
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
	clock_t tEnd = clock();
	//printf("Frame Time: %.2f\n", (double)(tEnd-tStart)/CLOCKS_PER_SEC);
    }

    return 0;
}
