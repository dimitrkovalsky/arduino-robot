#include "HandController.h"


void HandController::Setup(){
	m_pwm.begin();
	
	m_pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
}

void HandController::Execute(const char command[COMMAND_SIZE]){
	
	ComandBytesArray = command;

	ExecuteCommand();
}

void HandController::SetPosition(int servoNumber, int degrees){

	int servoCount =  m_servoLinks[servoNumber][0];

	//Serial.println(servoNumber);
	//Serial.println(servoCount);

	for (int i = 1; i <= servoCount; i++){

		int acualNumber = m_servoLinks[servoNumber][i];
		
		int pin = m_handServos[acualNumber][ServoPinIndex];
		int minValue = m_handServos[acualNumber][ServoMinIndex];
		int maxValue = m_handServos[acualNumber][ServoMaxIndex];

		long pulselength = map(degrees, 0, 180, minValue, maxValue);

		m_pwm.setPWM(pin, 0, pulselength);
	}
}

void HandController::ExecuteCommand(){

	int servoNumber = ComandBytesArray[0];
	int angle = ComandBytesArray[1];

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
