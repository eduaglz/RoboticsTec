/* 
* SearchOilRig.cpp
*
* Created: 10/10/2015 2:35:04 PM
* Author: edua_
*/


#include "SearchOilRig.h"
static SearchOilRig instance;

SearchOilRig* SearchOilRig::Instance(){

	return &instance;
}

void SearchOilRig::Enter(Robot* robot){
	
}

void SearchOilRig::Execute(Robot* robot){
	robot->Move(FORWARD,100);
	int j = 0;
	j += 2;
}

void SearchOilRig::Exit(Robot* robot){
	
}

SearchOilRig::~SearchOilRig(){
	
}