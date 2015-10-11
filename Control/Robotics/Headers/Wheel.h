/* 
* Wheel.h
*
* Created: 9/23/2015 7:10:14 PM
* Author: Eduardo
*/


#ifndef __WHEEL_H__
#define __WHEEL_H__
#include "PWM.h"
#include "Arduino.h"

class Wheel
{
//variables
public:
	int Speed;
protected:
private:
	PWM Pwm;
	uint8_t A;
	uint8_t B;
//functions
public:
	Wheel();
	Wheel(Timer timer, Channel channel, uint8_t pinA, uint8_t pinB);
	~Wheel();
	Wheel& operator=( const Wheel &c );
	void Forward(int speed);
	void Backward(int speed);
	void Stop();
protected:
private:
	Wheel( const Wheel &c );
	

}; //Wheel

#endif //__WHEEL_H__
