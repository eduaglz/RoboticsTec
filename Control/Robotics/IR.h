// IR.h

#ifndef _IR_h
#define _IR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class IR
{
	private:
		uint8_t Pin;
	protected:


	public:
		void Init(uint8_t pin);
		float read();
};
#endif

