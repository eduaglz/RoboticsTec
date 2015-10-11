/* 
* Robot.cpp
*
* Created: 9/20/2015 11:17:57 PM
* Author: Eduardo
*/


#include "../Headers/Robot.h"
#include "../States/SearchOilRig.h"


// Wheels used by the robot

Wheel FR(TIMER_1, CHANNEL_A, 10 ,11);
Wheel FL(TIMER_1, CHANNEL_B, 12, 13);
Wheel BR(TIMER_3, CHANNEL_A, 14, 15);
Wheel BL(TIMER_3, CHANNEL_B, 16, 17);

// default constructor
Robot::Robot()
{
	StateMachine = new FSM(this);
	StateMachine->SetCurrentState(SearchOilRig::Instance());
} //Robot

// default destructor
Robot::~Robot()
{
} //~Robot

void Robot::Move(Direction dir, int speed)
{
	switch(dir){
		case FORWARD:
			FR.Forward(speed);
			FL.Forward(speed);
			BR.Forward(speed);
			BL.Forward(speed);
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
			BR.Forward(speed);
			BL.Backward(speed);
			break;
		case LEFT_TURN:
			FR.Forward(speed);
			FL.Backward(speed);
			BR.Backward(speed);
			BL.Forward(speed);
			break;
	}
}

void Robot::Stop(){
	FR.Stop();
	FL.Stop();
	BR.Stop();
	BL.Stop();
}