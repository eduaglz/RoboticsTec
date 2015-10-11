/* 
* Robot.h
*
* Created: 9/20/2015 11:17:57 PM
* Author: Eduardo
*/


#ifndef __ROBOT_H__
#define __ROBOT_H__
#include "PWM.h"
#include "Wheel.h"
#include "FSM.h"

class FSM;

enum Direction{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	RIGHT_TURN,
	LEFT_TURN
	};

class Robot
{
//variables
public:
	FSM *StateMachine;
protected:
private:

//functions
public:
	Robot();
	~Robot();
	void Move(Direction dir, int speed);
	void Stop();
	
protected:
private:
	Robot( const Robot &c );
	Robot& operator=( const Robot &c );

}; //Robot

#endif //__ROBOT_H__
