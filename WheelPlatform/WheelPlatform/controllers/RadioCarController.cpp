#include "RadioCarController.h"

void RadioCarController::Setup(){
	pinMode( LED_PIN, OUTPUT );
	
	pinMode( ENA_PIN, OUTPUT );  // PWM ~ only !!!
	pinMode( IN1_PIN, OUTPUT );
	pinMode( IN2_PIN, OUTPUT );
	pinMode( IN3_PIN, OUTPUT );
	pinMode( IN4_PIN, OUTPUT );
	pinMode( ENB_PIN, OUTPUT );  // PWM ~ only !!!

	RobotSteeringServo.attach( SERVO_PIN );
	RobotSteeringServo.write( SERVO_ABSOLUTE_CENTER_ANGLE );
}



void RadioCarController::Execute(char *command){

	Comand_bytes_array = command;

	Execute_command();
}

void RadioCarController::Execute_command()
{
	Turn( & An_error_has_occured );
	Drive( & An_error_has_occured );
}

void RadioCarController::LED_blink()
{
	digitalWrite( LED_PIN, HIGH );
	delay( 500 );
	digitalWrite( LED_PIN, LOW );
	delay( 500 );
}

void RadioCarController::LED_blink(unsigned int Number_of_blinks)
{
	for( unsigned int I = 0; I < Number_of_blinks; I++ )
	{
		LED_blink();
	}
}

unsigned char RadioCarController::OneSymbolToByte(char Symbol, bool* An_error_has_occured_POINTER)
{
	switch( Symbol )
	{
		case '0' : return 0;
		case '1' : return 1;
		case '2' : return 2;
		case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
		case '7' : return 7;
		case '8' : return 8;
		case '9' : return 9;
		
		default :
		* An_error_has_occured_POINTER = true;  // Error
		return 0;  // Error
	}
}

unsigned char RadioCarController::TwoSymbolsToByte(char First_symbol, char Second_symbol, bool* An_error_has_occured_POINTER)
{
	return 10 * OneSymbolToByte( First_symbol, An_error_has_occured_POINTER ) +
	OneSymbolToByte( Second_symbol, An_error_has_occured_POINTER );
}

void RadioCarController::Turn(bool* An_error_has_occured_POINTER)
{
	unsigned char Input_turn_angle = TwoSymbolsToByte(
	*(Comand_bytes_array + 2),
	*(Comand_bytes_array + 3),
	An_error_has_occured_POINTER
	);
	
	unsigned long Servo_absolute_turn_angle;
	
	switch( *(Comand_bytes_array + 1) )
	{
		case LEFT :
		Servo_absolute_turn_angle = SERVO_ABSOLUTE_CENTER_ANGLE +
		SERVO_MAX_LEFT_ANGLE_SHIFT_FROM_THE_CENTER * Input_turn_angle / 99 ;
		break;
		
		case RIGHT :
		Servo_absolute_turn_angle = SERVO_ABSOLUTE_CENTER_ANGLE -
		SERVO_MAX_RIGHT_ANGLE_SHIFT_FROM_THE_CENTER * Input_turn_angle / 99 ;
		break;
		
		default :  // Error
		Servo_absolute_turn_angle = SERVO_ABSOLUTE_CENTER_ANGLE;
		* An_error_has_occured_POINTER = true;  // Error
	}
	
	// MIN and MAX servo angle thresholds
	if( Servo_absolute_turn_angle < SERVO_ABSOLUTE_MIN_ANGLE )
	{
		Servo_absolute_turn_angle = SERVO_ABSOLUTE_MIN_ANGLE;
	}
	else
	{
		if( Servo_absolute_turn_angle > SERVO_ABSOLUTE_MAX_ANGLE )
		{
			Servo_absolute_turn_angle = SERVO_ABSOLUTE_MAX_ANGLE;
		}
	}

	// Servo angle: the value to write to the servo, int - from 0 to 180
	// 0 - Max right    180 - Max left
	RobotSteeringServo.write( (int)Servo_absolute_turn_angle );
}

void RadioCarController::Drive(bool* An_error_has_occured_POINTER)
{
	unsigned char Input_speed =
	TwoSymbolsToByte( 
	*(Comand_bytes_array + 5),
	*(Comand_bytes_array + 6),
	An_error_has_occured_POINTER );
	
	// Absolute speed [0..255]
	unsigned long Absolute_speed = 255 * Input_speed / 99 ;
	
	// MAX robot speed threshold
	if( Absolute_speed > ABSOLUTE_MAX_SPEED )
	{
		Absolute_speed = ABSOLUTE_MAX_SPEED;
	}

	switch( *(Comand_bytes_array + 4 ) )
	{
		case FORWARD :
		// [0..255]
		analogWrite( ENA_PIN, (int)Absolute_speed );  // PWM - Absolute speed [0..255]
		digitalWrite( IN1_PIN, LOW );
		digitalWrite( IN2_PIN, HIGH );
		digitalWrite( IN3_PIN, HIGH );
		digitalWrite( IN4_PIN, LOW );
		analogWrite( ENB_PIN, (int)Absolute_speed );  // PWM - Absolute speed [0..255]
		break;
		
		case STOP :
		// [0..255]
		analogWrite( ENA_PIN, 0 );  // PWM - Absolute speed [0..255]
		digitalWrite( IN1_PIN, LOW );
		digitalWrite( IN2_PIN, LOW );
		digitalWrite( IN3_PIN, LOW );
		digitalWrite( IN4_PIN, LOW );
		analogWrite( ENB_PIN, 0 );  // PWM - Absolute speed [0..255]
		break;
		
		case BACKWARD :
		// [0..255]
		analogWrite( ENA_PIN, (int)Absolute_speed );  // PWM - Absolute speed [0..255]
		digitalWrite( IN1_PIN, HIGH );
		digitalWrite( IN2_PIN, LOW );
		digitalWrite( IN3_PIN, LOW );
		digitalWrite( IN4_PIN, HIGH );
		analogWrite( ENB_PIN, (int)Absolute_speed );  // PWM - Absolute speed [0..255]
		break;
		
		default :  // Error
		// [0..255]
		analogWrite( ENA_PIN, 0 );  // PWM - Absolute speed [0..255]
		digitalWrite( IN1_PIN, LOW );
		digitalWrite( IN2_PIN, LOW );
		digitalWrite( IN3_PIN, LOW );
		digitalWrite( IN4_PIN, LOW );
		analogWrite( ENB_PIN, 0 );  // PWM - Absolute speed [0..255]
		
		* An_error_has_occured_POINTER = true;  // Error
	}
}
