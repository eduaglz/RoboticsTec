/* 
* FrontCamera.cpp
*
* Created: 9/20/2015 11:44:35 PM
* Author: Eduardo
*/


#include "../Headers/FrontCamera.h"

// default constructor
FrontCamera::FrontCamera(RaspberryPi *pi)
{
	Pi = pi;
} //FrontCamera

// default destructor
FrontCamera::~FrontCamera()
{
} //~FrontCamera

bool FrontCamera::FindFigure(Figure figure)
{
	return false;
}

Pos* FrontCamera::GetFigurePosition(Figure figure)
{
	return 0;
}
