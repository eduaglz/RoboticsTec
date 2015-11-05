// 
// 
// 

#include "IR.h"

void IR::Init(uint8_t pin)
{
	Pin = pin;
}

float IR::read()
{
	//	We still need to do the convertion from voltage to actual distance
	float tmp = 2348/powf(analogRead(Pin),1.002);
	return tmp;
}

