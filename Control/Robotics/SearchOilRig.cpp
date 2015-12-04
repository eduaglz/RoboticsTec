/*
* SearchOilRig.cpp
*
* Created: 10/10/2015 2:35:04 PM
* Author: edua_
*/


#include "SearchOilRig.h"
#include "Comm.h"


void SearchOilRig::Enter(Robot* robot) {
	robot->Move(RIGHT, 80);
}

void SearchOilRig::Execute(Robot* robot) {
	bool leftOil, rightOil;
	robot->Move(RIGHT, 80);
	delay(4000);
	robot->Stop();
	Serial.write(GET_OIL_RIG);
	while(!Serial.available()) {
		delay(10);
	}
	uint8_t response = Serial.read();
	leftOil = response == 0x01;

	robot->Move(RIGHT, 80);
	delay(4000);
	robot->Stop();
	Serial.write(GET_OIL_RIG);
	while (!Serial.available()) {
		delay(10);
	}
	response = Serial.read();
	rightOil = response == 0x01;
	while(1){}
}

void SearchOilRig::Exit(Robot* robot) {

}

SearchOilRig SearchOilRigInstance;