/* 
* Camera.h
*
* Created: 9/20/2015 11:35:50 PM
* Author: Eduardo
*/


#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "RaspberryPi.h"

enum Figure{
	OIL_RIG,
	TRIANGLE,
	RECTANGLE,
	CIRCLE
	};
	
struct Pos{
	int x;
	int y;
	};

class Camera
{
//functions
public:
	virtual ~Camera(){}
	virtual bool FindFigure(Figure figure) = 0;
	virtual Pos* GetFigurePosition(Figure figure) = 0;

private:
	RaspberryPi *Pi;
}; //Camera

#endif //__CAMERA_H__
