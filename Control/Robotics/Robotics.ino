/*
 Name:		Robotics.ino
 Created:	10/25/2015 12:56:08 PM
 Author:	edua_
*/
#include "RightTurnState.h"
#include "MoveLeftState.h"
#include "MoveRightState.h"
#include "CrossWall.h"
#include <Servo.h>
#include "IR.h"
#include "GrabToolState.h"
#define COMPASS_DEBUG

//#include "Compass.h"
#include "Robot.h"
#include "Wheel.h"
#include <Wire.h>

short x;
byte xH, xL;
Robot robot;
/*
Wheel FR(TIMER_1, CHANNEL_A, 30, 31); // PWM pin 11
Wheel FL(TIMER_1, CHANNEL_B, 32, 33); // PWM pin 12
Wheel BR(TIMER_3, CHANNEL_A, 34, 35); // PWM pin 5
Wheel BL(TIMER_3, CHANNEL_B, 36, 37); // PWM pin 2
*/

enum COMMANDS {
	ACK,
	GET_FIGURE,
	GET_OIL_RIG
};

int i = 1;
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	// put your setup code here, to run once:
	//delay(1000);
	robot.Init();
	robot.StateMachine->SetCurrentState(&GrabTool);
	//robot.Camera_Servo.write(115);
	//robot.StateMachine->SetCurrentState(&RightTurn);
	//Serial.println("Initializing");
	//myCompass.init(true);
	//robot.Move(FORWARD, 50);
	//robot.Move(BACKWARD, 20);
	//BR.Forward(50);
	//robot.Move(RIGHT, 50);
	//TCCR1A = 0xA2;
	//TCCR1B = 0x1B;
	//TCCR3A = 0xA2;
	//TCCR3B = 0x1B;
	
}

// the loop function runs over and over again until power down or reset
void loop() {

	//degrees = (int)myCompass.getOrientation();
	//Serial.printf("Degrees %d \n", degrees);
	//Serial.println(degrees);
	//Serial.println(analogRead(9));
	//Serial.println(robot.Front_Left.read());
	robot.StateMachine->Update();
	//robot.Front_Right.read();
	//robot.Stop();

	//delay(500);
	//if (Serial.available())
	//{
	//	int pos = Serial.parseInt();
	//	robot.Camera_Servo.write(pos);
	//}

	//Serial.write(GET_OIL_RIG);
	//while(!Serial.available())
	//{ }
	//uint8_t res = Serial.read();
	//if (res)
	//{
	//	robot.Move(FORWARD, 20);
	//	delay(500);
	//	robot.Stop();
	//}
	//Serial.write(ACK);
}
