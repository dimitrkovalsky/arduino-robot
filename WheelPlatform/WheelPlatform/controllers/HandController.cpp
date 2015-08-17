#include "HandController.h"


void HandController::Setup(){
	m_pwm.begin();
	
	m_pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
}

void HandController::Execute(char command[COMMAND_SIZE]){
	
	ComandBytesArray = command;

	ExecuteCommand();
}

void HandController::SetPosition(int servoNumber, int degrees){

	int pin = m_handServos[servoNumber][ServoPinIndex];
	int minValue = m_handServos[servoNumber][ServoMinIndex];
	int maxValue = m_handServos[servoNumber][ServoMaxIndex];

	long pulselength = map(degrees, 0, 180, minValue, maxValue);

	m_pwm.setPWM(pin, 0, pulselength);
}

void HandController::ExecuteCommand(){

	int servoNumber = ComandBytesArray[1];
	int angle = ComandBytesArray[2];

	m_logAngle = angle;

	SetPosition( servoNumber, angle );
}

void HandController::Log()
{
	Serial.write(m_logAngle);

	Serial.write("L");
	Serial.write(5);
	delay(500);
}
