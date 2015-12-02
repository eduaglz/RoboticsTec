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
	//int val = analogRead(Pin);

	//if (val > 600)                             // lower boundary: 4 cm (3 cm means under the boundary)
	//{
	//	return (3);
	//}

	//if (val < 80)                             //upper boundary: 36 cm (returning 37 means over the boundary)
	//{
	//	return (37);
	//}

	//else
	//{
	//	return (1 / (0.000413153 * val - 0.0055266887));
	//}

	//	We still need to do the convertion from voltage to actual distance
	float accum = 10;
	for (int i = 9; i != 0; i--)
	{
		float tmp = 2348 / powf(analogRead(Pin), 1.002);
		accum += tmp;
		delay(5);
	}
	
	return accum/10;
}

