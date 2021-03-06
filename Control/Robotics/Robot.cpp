/*
* Robot.cpp
*
* Created: 9/20/2015 11:17:57 PM
* Author: Eduardo
*/


#include "Robot.h"
#include "SearchOilRig.h"


// Wheels used by the robot

//Wheel ; // PWM pin 11
//Wheel ; // PWM pin 12
//Wheel; // PWM pin 5
//Wheel; // PWM pin 2

// Sensors

// default constructor
Robot::Robot():FR(TIMER_1, CHANNEL_A, 30, 31), FL(TIMER_1, CHANNEL_B, 32, 33), BR(TIMER_3, CHANNEL_A, 34, 35), BL(TIMER_3, CHANNEL_B, 36, 37)
{	Line = 0;

	StateMachine = new FSM(this);
	//StateMachine->SetCurrentState((State *)&SearchOilRigInstance);

	//compass.init(true);
} //Robot

void Robot::Init() {
	// Init the sensors and servos
	Right.Init(IR_RIGHT_PIN); 
	Left.Init(IR_LEFT_PIN);
	Front.Init(IR_FRONT_PIN);
	Front_Left.Init(IR_FRONT_LEFT_PIN);
	Front_Right.Init(IR_FRONT_RIGHT_PIN);

	Gripper_Left.attach(GRIPPER_LEFT_PIN);
	Gripper_Right.attach(GRIPPER_RIGHT_PIN);
	Gripper_Lifter.attach(GRIPPER_LIFTER_PIN);
	Camera_Servo.attach(CAMERA_PIN);
}
  // default destructor
Robot::~Robot()
{
	
} //~Robot

void Robot::Move(Direction dir, int speed)
{
	switch (dir) {
	case FORWARD:
		BR.Forward(speed);
		BL.Forward(speed);
		FR.Forward(speed);
		FL.Forward(speed);
		break;
	case BACKWARD:
		FR.Backward(speed);
		FL.Backward(speed);
		BR.Backward(speed);
		BL.Backward(speed);
		break;
	case LEFT:
		FR.Forward(speed);
		FL.Backward(speed);
		BR.Backward(speed);
		BL.Forward(speed);
		break;
	case RIGHT:
		FR.Backward(speed);
		FL.Forward(speed);
		BR.Forward(speed);
		BL.Backward(speed);
		break;
	case RIGHT_TURN:
		FR.Backward(speed);
		FL.Forward(speed);
		BR.Backward(speed);
		BL.Forward(speed);
		break;

	case LEFT_TURN:
		FR.Forward(speed);
		FL.Backward(speed);
		BR.Forward(speed);
		BL.Backward(speed);
		break;
	}
}

void Robot::Stop() {
	FR.Stop();
	FL.Stop();
	BR.Stop();
	BL.Stop();
}