/*
* Wheel.cpp
*
* Created: 9/23/2015 7:10:14 PM
* Author: Eduardo
*/


#include "Wheel.h"

// default constructor
Wheel::Wheel() {}

Wheel::Wheel(Timer timer, Channel channel, uint8_t pinA, uint8_t pinB) :Pwm(timer, channel, 50, 0, 64)
{
	A = pinA;
	B = pinB;
	pinMode(A, OUTPUT);
	pinMode(B, OUTPUT);

} //Wheel

  // default destructor
Wheel::~Wheel()
{
} //~Wheel

void Wheel::Forward(int speed)
{
	digitalWrite(A, HIGH);
	digitalWrite(B, LOW);
	Pwm.SetDutyCycle(speed);
}

void Wheel::Backward(int speed)
{
	digitalWrite(A, LOW);
	digitalWrite(B, HIGH);
	Pwm.SetDutyCycle(speed);
}

void Wheel::Stop()
{
	digitalWrite(A, LOW);
	digitalWrite(B, LOW);
}
