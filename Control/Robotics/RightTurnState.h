// RightTurnState.h

#ifndef _RIGHTTURNSTATE_h
#define _RIGHTTURNSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Robot.h"

class RightTurnState : public State
{
	public:
		virtual void Enter(Robot* robot);
		virtual void Execute(Robot* robot);
		virtual void Exit(Robot* robot);
};

extern RightTurnState RightTurn;

#endif

