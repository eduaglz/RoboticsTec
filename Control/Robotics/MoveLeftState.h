// MoveLeftState.h

#ifndef _MOVELEFTSTATE_h
#define _MOVELEFTSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Robot.h"

class MoveLeftState:public State
{
 protected:
public:
	virtual void Enter(Robot* robot);
	virtual void Execute(Robot* robot);
	virtual void Exit(Robot* robot);
 public:
	void init();
};

extern MoveLeftState MoveLeft;

#endif

