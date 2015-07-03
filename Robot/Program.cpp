//Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (*func)()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

int main(void)
{
	initVariant();

	#if defined(USBCON)
	USBDevice.attach();
	#endif
	
	//init
	
	for (;;) {
		//loop
	}
	
	return 0;
}

