#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <list>
 

using namespace std;
using namespace cv;
char key;
Mat frame;

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

Features fillRegion(Mat &src, Mat &dst, Point start)
{
    int size = 0;
    list<Point> cadena;
    cadena.push_back(start);
    Features features;
    features.M00 = features. M10 = features.M01 = 0;
    features.M20 = features.M02 = features.M11 = 0;
    Vec3b color = getRandomColor();
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

        if(left.y >= 0 && dst.at<Vec3b>(left) == Vec3b(0,0,0) && src.at<uchar>(left)!= 0)
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
    printf( "F1: %f F2: %f\n", features.F1, features.F2 );
    if(features.F1 > 0.160 && features.F1 < 0.195 && features.F2 > 0.002 && features.F2 < 0.007)
    	cout << "Flama" << endl;
    else
    	cout << "Nada" << endl;
    return features;
}

void getShapes(Mat &img, Mat &out)
{
	short nRows = img.rows;
	short nCols = img.cols;
	int row,col;
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
				Features f = fillRegion(img, out, p);
				// printf("%s: %d\n", "Region found with area",f.M00);
			}
		}
	}
}

int main()
{
    cvNamedWindow("Original", 1);    //Create window
    cvNamedWindow("Threshold", 1);
    cvNamedWindow("Segment", 1);


	setMouseCallback("Original", mouseCallback);

	VideoCapture camera(0);
    camera.set(CV_CAP_PROP_FRAME_WIDTH,320);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,240);

    if(!camera.isOpened()){
		cerr << "ERROR: Could not open camera" << endl;
		return 1;
	}

    while(1){ 
    	// Create infinte loop for live streaming
		Mat threshold(240,320,CV_8UC1,255);
		camera >> frame;
	    cvtColor(frame, frame, CV_RGB2HSV);
		inRange(frame,Scalar(0,0,0), Scalar(179,100,50), threshold);
		erode(threshold, threshold, Mat());
		dilate(threshold, threshold, Mat());
		Mat out( 240, 320, CV_8UC3, Scalar(0,0,0));
		getShapes(threshold, out);
		imshow("Threshold", threshold);
		imshow("Segment", out);   // Show image frames on created window
	    imshow("Original", frame);
		key = cvWaitKey(10);     // Capture Keyboard stroke
        if (char(key) == 27){
            break;      // If you hit ESC key loop will break.
        }
        out.release();
    }

    return 0;
}
