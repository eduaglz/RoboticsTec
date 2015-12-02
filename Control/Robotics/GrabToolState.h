#pragma once
#include "State.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "Robot.h"

class GrabToolState :
	public State
{
public:
	virtual void Enter(Robot* robot);
	virtual void Execute(Robot* robot);
	virtual void Exit(Robot* robot);
};

extern GrabToolState GrabTool;