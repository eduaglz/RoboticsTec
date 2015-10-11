/* 
* State.h
*
* Created: 10/10/2015 2:09:44 PM
* Author: edua_
*/


#ifndef __STATE_H__
#define __STATE_H__

#include "Robot.h"

class Robot;

class State
{
//functions
public:
	virtual ~State(){}
	virtual void Enter(Robot *robot) = 0;
	virtual void Execute(Robot *robot) = 0;
	virtual void Exit(Robot *robot) = 0;
}; //State

#endif //__STATE_H__
