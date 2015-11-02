// FSM.h

#ifndef _FSM_h
#define _FSM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Robot.h"
#include "State.h"

class Robot;
class State;

class FSM
{
	//variables
public:
protected:
private:
	Robot *robot;
	State *currentState;
	State *previousState;
	State *globalState;

	//functions
public:
	void SetCurrentState(State* state);
	void SetGlobalState(State* state);
	void SetPreviousState(State* state);
	void Update();
	void ChangeState(State* newState);
	FSM(Robot *owner);
	~FSM();
protected:
private:
	FSM(const FSM &c);
	FSM& operator=(const FSM &c);
}; //FSM

#endif

