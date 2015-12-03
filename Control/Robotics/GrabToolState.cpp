// 
// 
// 

#include "GrabToolState.h"

void GrabToolState::Enter(Robot* robot) {
	robot->Move(FORWARD, 30);
}

void GrabToolState::Execute(Robot* robot) {
	Serial.println("Cerrando");
	robot->Gripper_Left.write(180);
	robot->Gripper_Right.write(0);
	delay(500);
	robot->Gripper_Lifter.write(122);
	delay(2000);
	Serial.println("Abriendo");
	robot->Gripper_Lifter.write(40);
	delay(500);
	robot->Gripper_Left.write(100);
	robot->Gripper_Right.write(80);


	delay(2000);
}

void GrabToolState::Exit(Robot* robot) {
	robot->Stop();
}


GrabToolState GrabTool;