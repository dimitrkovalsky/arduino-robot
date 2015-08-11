#ifndef __COMMANDCONTROLLER_H__
#define __COMMANDCONTROLLER_H__

#include "HardwareSerial.h"

#include "RadioCarController.h"
#include "HandController.h"
#include "Config.h"

class CommandController
{
	private:
	RadioCarController RadioCar;
	HandController Hand;

	char Comand_bytes_array[ COMMAND_SIZE ] = { 'H', 'L', '0', '0', 'S', '0', '0'};

	char ComandOwners[2] = { 'H', 'W' };

	
	bool HasError = false;
	unsigned char m_size = 0;

	public:
	void Setup();
	void Loop();

	private:
	void ExecuteCommand( bool* hasError );
};

#endif
