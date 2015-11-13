// 
// 
// 

#include "MoveRightState.h"
#include "MoveLeftState.h"
#include "CrossWall.h"

void MoveRightState::Enter(Robot* robot)
{
	robot->Move(RIGHT, 50);
}

void MoveRightState::Execute(Robot* robot)
{
	Serial.println("MoveRightState");
	float rightDistance = robot->Front_Right.read();
	float leftDistance = robot->Front_Left.read();
	float rightSensor = robot->Right.read();
	Serial.println(rightSensor);
	if (rightSensor > 12)
	{
		robot->StateMachine->ChangeState(&MoveLeft);
	}
	if (rightDistance > 10 && leftDistance > 10)
	{
		delay(300);
		robot->StateMachine->ChangeState(&CrossWall);
	}

}

void MoveRightState::Exit(Robot* robot)
{
	robot->Stop();
}


MoveRightState MoveRight;

