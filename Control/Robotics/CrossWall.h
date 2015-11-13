// CrossWall.h

#ifndef _CROSSWALL_h
#define _CROSSWALL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Robot.h"

class CrossWallState: public State
{
public:
	virtual void Enter(Robot* robot);
	virtual void Execute(Robot* robot);
	virtual void Exit(Robot* robot);
};

extern CrossWallState CrossWall;

#endif

