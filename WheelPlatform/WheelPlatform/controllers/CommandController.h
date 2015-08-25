#ifndef __COMMANDCONTROLLER_H__
#define __COMMANDCONTROLLER_H__

#include "HardwareSerial.h"
#include "proxies/WakeUpSerial.h"
#include "proxies/ReciveEventHandler.h"

#include "RadioCarController.h"
#include "HandController.h"
#include "Config.h"

class CommandController
{
	private:
	WakeUpSerial* m_wakeUpSerial;

	RadioCarController RadioCar;
	HandController Hand;

	char Comand_bytes_array[ COMMAND_SIZE ] = { 'H', 'L', '0', '0', 'S', '0', '0'};

	char ComandOwners[2] = { 'H', 'W' };

	
	bool HasError = false;
	unsigned char m_size = 0;

	public:
	CommandController();

	void Loop();
	void RaiseSerialReciveEvent();

	private:
	void ReciveCommandHandler(const Object* sender, const ReciveEventArgs* args);
};

#endif
