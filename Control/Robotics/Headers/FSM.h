/* 
* FSM.h
*
* Created: 10/10/2015 2:11:46 PM
* Author: edua_
*/


#ifndef __FSM_H__
#define __FSM_H__
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
	FSM( const FSM &c );
	FSM& operator=( const FSM &c );
}; //FSM

#endif //__FSM_H__
