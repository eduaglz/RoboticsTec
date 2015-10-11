/* 
* FSM.cpp
*
* Created: 10/10/2015 2:11:46 PM
* Author: edua_
*/


#include "../Headers/FSM.h"
#include <stdlib.h>

// default constructor
FSM::FSM(Robot* owner):robot(owner),currentState(NULL),previousState(NULL), globalState(NULL)
{
} //FSM

// default destructor
FSM::~FSM()
{
} //~FSM

void FSM::SetCurrentState(State* state){
	currentState = state;
}

void FSM::SetGlobalState(State* state){
	globalState = state;
}

void FSM::SetPreviousState(State* state){
	previousState = state;
}

void FSM::Update(){
	if(globalState) globalState->Execute(robot);
	if(currentState) currentState->Execute(robot);
}

void FSM::ChangeState(State* newState){
	previousState = currentState;
	if(currentState) currentState->Exit(robot);
	currentState = newState;
	currentState->Enter(robot);
}