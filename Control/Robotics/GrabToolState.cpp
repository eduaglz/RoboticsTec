// 
// 
// 

#include "GrabToolState.h"
#include "MoveLeftState.h"

void GrabToolState::Enter(Robot* robot) {
	robot->Gripper_Lifter.write(122);
	robot->Gripper_Left.write(100);
	robot->Gripper_Right.write(80);
}

void GrabToolState::Execute(Robot* robot) {
	robot->Move(FORWARD, 50);
	float left, mid, right;
	do {
		left = robot->Front_Left.read();
		mid = robot->Front.read();
		right = robot->Front_Right.read();
	} while (left >= 10 && mid >= 10 && right >= 10);
	robot->Stop();
	robot->Move(RIGHT, 50);
	do {
		mid = robot->Front.read();
	} while (mid >= 10);
	delay(300);
	robot->Stop();
	delay(1000);
	robot->Move(FORWARD, 50);
	do {
		mid = robot->Front.read();
	} while (mid >= 5);
	delay(50);
	robot->Stop();
	//Serial.println("Abriendo");
	robot->Gripper_Left.write(100);
	robot->Gripper_Right.write(80);
	delay(500);
	robot->Gripper_Lifter.write(40);
	delay(1000);
	//Serial.println("Cerrando");
	robot->Gripper_Left.write(180);
	robot->Gripper_Right.write(0);
	delay(500);
	robot->Gripper_Lifter.write(122);
	delay(2000);
	//Abre para reacomodarse
	robot->Gripper_Left.write(100);
	robot->Gripper_Right.write(80);
	delay(500);
	robot->Gripper_Left.write(180);
	robot->Gripper_Right.write(0);
	//float centro = robot->Front.read();
	//Serial.println(centro);
	//if (centro <= 5) {
	//	robot->Move(FORWARD, 50);
	//	delay(200);
	//	robot->Stop();
	//	Serial.println("Abriendo");
	//	robot->Gripper_Left.write(100);
	//	robot->Gripper_Right.write(80);
	//	delay(500);
	//	robot->Gripper_Lifter.write(40);
	//	delay(1000);
	//	Serial.println("Cerrando");
	//	robot->Gripper_Left.write(180);
	//	robot->Gripper_Right.write(0);
	//	delay(500);
	//	robot->Gripper_Lifter.write(122);
	//	delay(2000);
	//	//Abre para reacomodarse
	//	robot->Gripper_Left.write(100);
	//	robot->Gripper_Right.write(80);
	//	delay(500);
	//	robot->Gripper_Left.write(180);
	//	robot->Gripper_Right.write(0);
	//}
	robot->Move(BACKWARD, 100);
	delay(1000);
	robot->Move(LEFT_TURN, 80);
	delay(2500);
	robot->Stop();
	robot->StateMachine->ChangeState(&MoveLeft);
}

void GrabToolState::Exit(Robot* robot) {
	robot->Stop();
}


GrabToolState GrabTool;