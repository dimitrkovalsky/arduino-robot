#ifndef __HANDCONTROLLER_H__
#define __HANDCONTROLLER_H__

#include <Wire\Wire.h>
#include <PWM\Adafruit_PWMServoDriver.h>
#include "Config.h"
#include "Parser.h"
#include "HardwareSerial.h"

class HandController
{
	//variables
	public:
	protected:
	private:
	int m_logNumber = 7;
	int m_logAngle = 89;


	int m_handServos[6][3] = {
		{0, 160, 510},
		{3, 160, 510},
		{7, 160, 490},
		{8, 150, 510},
		{12, 150, 490},
		{15, 150, 500}
	};
	#define	ServoPinIndex 0
	#define ServoMinIndex 1
	#define ServoMaxIndex 2

	Adafruit_PWMServoDriver m_pwm = Adafruit_PWMServoDriver(0x41);

	// Depending on your servo make, the pulse width min and max may vary, you
	// want these to be as small/large as possible without hitting the hard stop
	// for max range. You'll have to tweak them as necessary to match the servos you
	// have!
	//#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
	//#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)


	char *ComandBytesArray;

	//functions
	public:
	void Setup();
	void Execute(char command[COMMAND_SIZE]);
	void Log();

	protected:
	private:

	void SetPosition(int servoNumber, int degrees);
	void ExecuteCommand();
}; //HandController

#endif //__HANDCONTROLLER_H__
