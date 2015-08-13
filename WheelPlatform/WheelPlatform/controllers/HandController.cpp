#include "HandController.h"


void HandController::Setup(){
	m_pwm.begin();
	
	m_pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
	/*
	SetPosition(0, 90);

	SetPosition(1, 20);

	SetPosition(2, 50);

	SetPosition(3, 90);

	SetPosition(4, 90);

	SetPosition(5, 90);
	*/
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

	unsigned char servoNumber = 0;
	if(!TryGetServoNumber( &servoNumber )){
		return;
	}
	
	unsigned char angle = 0;
	if(!TryGetAngle( &angle )){
		return;
	}
	
	m_logAngle = angle;
	m_logNumber = servoNumber;

	SetPosition( (int)servoNumber, (int)angle );
}

bool HandController::TryGetServoNumber(unsigned char *number){

	*number = ComandBytesArray[1];
	
	return true;
}

bool HandController::TryGetAngle( unsigned char *angle ){
	
	*angle = ComandBytesArray[2];
	
	//need to validate angle respect to the current servo

	return true;
}

void HandController::Log()
{
	Serial.write(m_logNumber);
	Serial.write("   ");
	Serial.write(m_logAngle);
}
