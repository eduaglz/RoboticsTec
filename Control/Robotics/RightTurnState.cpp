// 
// 
// 

#include "RightTurnState.h"
#include "MoveRightState.h"

void RightTurnState::Enter(Robot* robot)
{
	//robot->Move(RIGHT_TURN, 50);
}

void RightTurnState::Execute(Robot* robot)
{
	delay(4700);
	//float dir = robot->compass.getOrientation();
	//if (dir > 89 && dir < 91)
	//	robot->Stop();
	robot->StateMachine->SetCurrentState(&MoveRight);
}

void RightTurnState::Exit(Robot* robot)
{
	//robot->Stop();
}


RightTurnState RightTurn;

