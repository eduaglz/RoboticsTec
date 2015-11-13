// 
// 
// 

#include "MoveLeftState.h"
#include "MoveRightState.h"
#include "CrossWall.h"

void MoveLeftState::Enter(Robot* robot)
{
	robot->Move(LEFT, 50);
}

void MoveLeftState::Execute(Robot* robot)
{
	Serial.println("MoveLeftState");
	float rightDistance = robot->Front_Right.read();
	float leftDistance = robot->Front_Left.read();
	float leftSide = robot->Left.read();
	Serial.println(leftSide);
	if (rightDistance > 10 && leftDistance > 10)
	{
		delay(300);
		robot->StateMachine->ChangeState(&CrossWall);
	}
	if (leftSide > 12)
	{
		robot->StateMachine->ChangeState(&MoveRight);
	}
}

void MoveLeftState::Exit(Robot* robot)
{
	robot->Stop();
}


MoveLeftState MoveLeft;

