#ifndef __RADIOCARCONTROLLER_H__
#define __RADIOCARCONTROLLER_H__

#include <Arduino.h>
#include <Servo.h>

class RadioCarController{
	//variables
	private:
	#pragma region Pins
	// Pins ---------------------------------------------

	#define SERVO_PIN 12

	#define ENA_PIN 6  // PWM ~ only !!!
	#define IN1_PIN 2
	#define IN2_PIN 3

	#define IN3_PIN 4
	#define IN4_PIN 5
	#define ENB_PIN 7  // PWM ~ only !!!

	#define LED_PIN 13

	//---------------------------------------------------
	#pragma endregion Pins

	#define LEFT 'L'
	#define RIGHT 'R'

	#define FORWARD 'F'
	#define STOP 'S'
	#define BACKWARD 'B'

	Servo RobotSteeringServo;

	//const unsigned char COMMAND_SIZE = 6;
	#define COMMAND_SIZE 6
	char Comand_bytes_array[ COMMAND_SIZE ] = { 'L', '0', '0', 'S', '0', '0' };

	// 0 - Max right    180 - Max left
	#define SERVO_ABSOLUTE_CENTER_ANGLE 102  // [0..180]  Degrees

	#define SERVO_MAX_LEFT_ANGLE_SHIFT_FROM_THE_CENTER 54  // Degrees
	#define SERVO_MAX_RIGHT_ANGLE_SHIFT_FROM_THE_CENTER 48  // Degrees

	static const int SERVO_ABSOLUTE_MIN_ANGLE =
	SERVO_ABSOLUTE_CENTER_ANGLE -                 // Turn right
	SERVO_MAX_RIGHT_ANGLE_SHIFT_FROM_THE_CENTER;  // = 102 - 48 = 54  Degrees

	static const int SERVO_ABSOLUTE_MAX_ANGLE =
	SERVO_ABSOLUTE_CENTER_ANGLE +                // Turn left
	SERVO_MAX_LEFT_ANGLE_SHIFT_FROM_THE_CENTER;  // = 102 + 54 = 156  Degrees

	// MAX robot speed threshold
	#define ABSOLUTE_MAX_SPEED 255 // [0..255]
	
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
