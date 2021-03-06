// 
// 
// 

#include "CrossWall.h"
#include "MoveRightState.h"
#include "RightTurnState.h"

void CrossWallState::Enter(Robot* robot) {
	robot->Move(FORWARD, 80);
}

void CrossWallState::Execute(Robot* robot) {
	Serial.println("CrossWallState");
	float rightDistance = robot->Front_Right.read();
	float leftDistance = robot->Front_Left.read();

	if (rightDistance < 10 || leftDistance < 10)
	{
		//robot->Line++;
		//if (robot->Line == 4)
		//{
		//	robot->Line = 0;
		//	robot->StateMachine->ChangeState(&RightTurn);
		//}
		//else
			robot->StateMachine->ChangeState(&MoveRight);
	}
}

void CrossWallState::Exit(Robot* robot) {
	robot->Stop();
}


CrossWallState CrossWall;

