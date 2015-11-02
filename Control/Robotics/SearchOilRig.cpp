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
	pos += 100;
	Serial.print("Moviendo Robot");
	Serial.println(pos);
	robot->Move(FORWARD, 100);
}

void SearchOilRig::Exit(Robot* robot) {

}

SearchOilRig::~SearchOilRig() {

}

SearchOilRig SearchOilRigInstance;