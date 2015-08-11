#include "HandController.h"


void HandController::Setup(){
	m_pwm.begin();
	
	m_pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
}

void HandController::Loop(){

	SetPosition(0, 90);
	delay(10000);

	SetPosition(1, 90);
	delay(10000);

	SetPosition(2, 90);
	delay(10000);

	SetPosition(3, 90);
	delay(10000);

	SetPosition(4, 90);
	delay(10000);

	SetPosition(5, 90);
	delay(10000);

}

void HandController::SetPosition(int servoNumber, int degrees){

	int pin = m_handServos[servoNumber][ServoPinIndex];
	int minValue = m_handServos[servoNumber][ServoMinIndex];
	int maxValue = m_handServos[servoNumber][ServoMaxIndex];

	long pulselength = map(degrees, 0, 180, minValue, maxValue);

	m_pwm.setPWM(pin, 0, pulselength);
}
