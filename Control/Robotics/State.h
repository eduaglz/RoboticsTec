// State.h

#ifndef _STATE_h
#define _STATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Robot.h"

class Robot;

class State
{
	//functions
public:
	virtual ~State() {}
	virtual void Enter(Robot *robot) = 0;
	virtual void Execute(Robot *robot) = 0;
	virtual void Exit(Robot *robot) = 0;
}; //State

#endif

