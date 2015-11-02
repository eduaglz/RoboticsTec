// Wheel.h

#ifndef _WHEEL_h
#define _WHEEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "PWM.h"

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
	Wheel& operator=(const Wheel &c);
	void Forward(int speed);
	void Backward(int speed);
	void Stop();
protected:
private:
	Wheel(const Wheel &c);


}; //Wheel

#endif

