// Robot.h

#ifndef _ROBOT_h
#define _ROBOT_h



#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Servo.h>
#include "PWM.h"
#include "Wheel.h"
#include "FSM.h"
#include "IR.h"
#include "Compass.h"

#define	IR_RIGHT_PIN 20
#define	IR_LEFT_PIN 21
#define	IR_FRONT_PIN 22
#define	IR_FRONT_RIGHT_PIN	23
#define	IR_FRONT_LEFT_PIN	24

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
	FSM	*StateMachine;

	IR	Right;
	IR	Left;
	IR	Front;
	IR	Front_Right;
	IR	Front_Left;

	Compass compass;

	Servo Gripper_Right;
	Servo Gripper_Left;

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

