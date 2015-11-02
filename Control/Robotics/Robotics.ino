/*
 Name:		Robotics.ino
 Created:	10/25/2015 12:56:08 PM
 Author:	edua_
*/
#define COMPASS_DEBUG

#include "Compass.h"
#include "Robot.h"
#include <Wire.h>
#include "Robot.h"
#include "Compass.h"
short x;
byte xH, xL;
Compass myCompass;
int degrees;
// the setup function runs once when you press reset or power the board
void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	//Serial.println("Initializing");
	myCompass.init(true);


}

// the loop function runs over and over again until power down or reset
void loop() {
	degrees = (int)myCompass.getOrientation();
	//Serial.printf("Degrees %d \n", degrees);
	//Serial.println(degrees);
	delay(100);
}
