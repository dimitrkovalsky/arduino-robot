#ifndef __RADIOCARCONTROLLER_H__
#define __RADIOCARCONTROLLER_H__

#include <Arduino.h>
#include <Servo.h>

class RadioCarController{
	//variables
	private:
	#pragma region Pins
	// Pins ---------------------------------------------

	const int SERVO_PIN = 12;

	const int ENA_PIN = 6;  // PWM ~ only !!!
	const int IN1_PIN = 7;
	const int IN2_PIN = 4;

	const int IN3_PIN = 3;
	const int IN4_PIN = 2;
	const int ENB_PIN = 5;  // PWM ~ only !!!

	const int LED_PIN = 13;

	//---------------------------------------------------
	#pragma endregion Pins

	static const char LEFT = 'L';
	static const char RIGHT = 'R';

	static const char FORWARD = 'F';
	static const char STOP = 'S';
	static const char BACKWARD = 'B';

	Servo RobotSteeringServo;

	//const unsigned char COMMAND_SIZE = 6;
	#define COMMAND_SIZE 6
	char Comand_bytes_array[ COMMAND_SIZE ] = { 'L', '0', '0', 'S', '0', '0' };

	// 0 - Max right    180 - Max left
	const int SERVO_ABSOLUTE_CENTER_ANGLE = 102;  // [0..180]  Degrees

	const int SERVO_MAX_LEFT_ANGLE_SHIFT_FROM_THE_CENTER = 54;  // Degrees
	const int SERVO_MAX_RIGHT_ANGLE_SHIFT_FROM_THE_CENTER = 48;  // Degrees

	const int SERVO_ABSOLUTE_MIN_ANGLE =
	SERVO_ABSOLUTE_CENTER_ANGLE -                 // Turn right
	SERVO_MAX_RIGHT_ANGLE_SHIFT_FROM_THE_CENTER;  // = 102 - 48 = 54  Degrees

	const int SERVO_ABSOLUTE_MAX_ANGLE =
	SERVO_ABSOLUTE_CENTER_ANGLE +                // Turn left
	SERVO_MAX_LEFT_ANGLE_SHIFT_FROM_THE_CENTER;  // = 102 + 54 = 156  Degrees

	// MAX robot speed threshold
	const int ABSOLUTE_MAX_SPEED = 255; // [0..255]
	
	unsigned char I = 0;
	bool An_error_has_occured = false;
	
	
	public:
	
	void Setup();
	void Loop();
	
	private:
	void Execute_command();
	unsigned char OneSymbolToByte( char Symbol, bool* An_error_has_occured_POINTER );
	void Turn( bool* An_error_has_occured_POINTER );
	void Drive( bool* An_error_has_occured_POINTER );
	
	unsigned char TwoSymbolsToByte( 
		char First_symbol,
		char Second_symbol,
		bool* An_error_has_occured_POINTER 
	);
	
	void LED_blink();
	void LED_blink( unsigned int Number_of_blinks );

}; //RadioCarController

#endif //__RADIOCARCONTROLLER_H__
