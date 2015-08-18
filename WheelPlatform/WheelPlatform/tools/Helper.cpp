#include "Helper.h"

void Helper::LED_blink()
{
	digitalWrite( LED_PIN, HIGH );
	delay( 500 );
	digitalWrite( LED_PIN, LOW );
	delay( 500 );
}

void Helper::LED_blink(unsigned int Number_of_blinks)
{
	
	pinMode( LED_PIN, OUTPUT );
	
	for( unsigned int I = 0; I < Number_of_blinks; I++ )
	{
		LED_blink();
	}
}