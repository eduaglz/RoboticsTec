// Robot.h

#ifndef _ROBOT_h
#define _ROBOT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "PWM.h"
#include "Wheel.h"
#include "FSM.h"

class FSM;

enum Direction {
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
	Robot(const Robot &c);
	Robot& operator=(const Robot &c);

}; //Robot

#endif

