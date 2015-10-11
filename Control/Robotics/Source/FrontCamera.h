/* 
* FrontCamera.h
*
* Created: 9/20/2015 11:44:35 PM
* Author: Eduardo
*/


#ifndef __FRONTCAMERA_H__
#define __FRONTCAMERA_H__
#include "../Headers/RaspberryPi.h"

class FrontCamera : public Camera
{
//variables
public:
protected:
private:

//functions
public:
	FrontCamera(RaspberryPi *pi);
	~FrontCamera();
protected:
private:
	FrontCamera( const FrontCamera &c );
	FrontCamera& operator=( const FrontCamera &c );

}; //FrontCamera

#endif //__FRONTCAMERA_H__
