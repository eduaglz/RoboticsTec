/*
* SearchOilRig.cpp
*
* Created: 10/10/2015 2:35:04 PM
* Author: edua_
*/


#include "SearchOilRig.h"


void SearchOilRig::Enter(Robot* robot) {

}

void SearchOilRig::Execute(Robot* robot) {
	robot->Move(RIGHT,50);
	delay(1000);
	robot->Stop();
	Serial.write(0x20);
	while(!Serial.available()) {
		delay(10);
	}
	char response = Serial.read();
	
}

void SearchOilRig::Exit(Robot* robot) {

}

SearchOilRig::~SearchOilRig() {

}

SearchOilRig SearchOilRigInstance;