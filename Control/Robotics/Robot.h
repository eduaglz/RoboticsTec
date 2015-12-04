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
//#include "Compass.h"

#define	IR_RIGHT_PIN		8
#define	IR_LEFT_PIN			9
#define	IR_FRONT_PIN		10
#define	IR_FRONT_LEFT_PIN	11
#define	IR_FRONT_RIGHT_PIN	12

#define GRIPPER_LEFT_PIN	25
#define GRIPPER_RIGHT_PIN	27
#define GRIPPER_LIFTER_PIN	26
#define CAMERA_PIN			28

class FSM;

enum Direction {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	RIGHT_TURN,
	LEFT_TURN,
	RIGHT_WHEELS
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

	Wheel FL, FR, BL, BR;

	//Compass compass;

	Servo Gripper_Right;
	Servo Gripper_Left;
	Servo Gripper_Lifter;
	Servo Camera_Servo;

	int Line;

protected:
private:

	//functions
public:
	Robot();
	~Robot();
	void Init();
	void Move(Direction dir, int speed);
	void Stop();

protected:
private:
	Robot(const Robot &c);
	Robot& operator=(const Robot &c);

}; //Robot

#endif

