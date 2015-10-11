/* 
* Servo.cpp
*
* Created: 10/3/2015 10:02:05 PM
* Author: edua_
*/


#include "../Headers/Servo.h"

// default constructor
Servo::Servo(Timer timer, Channel channel):Pwm(timer,channel,50,2,8)
{
	Angle = 0;
} //Servo

// default destructor
Servo::~Servo()
{
} //~Servo
