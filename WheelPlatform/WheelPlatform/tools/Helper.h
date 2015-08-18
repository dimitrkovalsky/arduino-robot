#ifndef __HELPER_H__
#define __HELPER_H__

#include "Arduino.h"
#define LED_PIN 13

class Helper
{
	
public:
static void LED_blink();

static void LED_blink(unsigned int Number_of_blinks);
}; //Helper

#endif //__HELPER_H__
