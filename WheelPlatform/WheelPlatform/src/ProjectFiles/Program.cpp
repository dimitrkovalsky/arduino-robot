/*
* Program.cpp
*
* Created: 27.01.2015 23:44:49
*  Author: Yaroslav
*/
#include "Program.h"

void setup(){
	pinMode(13, OUTPUT);
	Serial.begin(9600);
	Serial.print("Hello world");
}

void loop(){
	digitalWrite(13, LOW);
	delay(1000);
	
	digitalWrite(13, HIGH);
	delay(1000);
}