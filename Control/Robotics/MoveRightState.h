// MoveRightState.h

#ifndef _MOVERIGHTSTATE_h
#define _MOVERIGHTSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Robot.h"

class MoveRightState : public State
{
 protected:


 public:
	 virtual void Enter(Robot* robot);
	 virtual void Execute(Robot* robot);
	 virtual void Exit(Robot* robot);
};

extern MoveRightState MoveRight;

#endif

