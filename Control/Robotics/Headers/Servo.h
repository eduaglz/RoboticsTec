/* 
* Servo.h
*
* Created: 10/3/2015 10:02:06 PM
* Author: edua_
*/


#ifndef __SERVO_H__
#define __SERVO_H__

#include "PWM.h"

class Servo
{
//variables
public:
protected:
private:
PWM Pwm;
float Angle;
//functions
public:
	Servo(Timer timer, Channel channel);
	~Servo();
	void SetAngle(float angle);
	float GetAngle();
protected:
private:
	Servo( const Servo &c );
	Servo& operator=( const Servo &c );

}; //Servo

#endif //__SERVO_H__
