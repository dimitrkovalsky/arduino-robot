#ifndef WAKEPACKET_H_
#define WAKEPACKET_H_

#include "Arduino.h"
#include "ISerial.h"

class WakePacket  {
	protected:
	
	const ISerial& _wakeUpSerial;
	unsigned char _address = 0;
	unsigned char _command = 0;
	unsigned char _dataSize = 0;
	char *_data = NULL;
	unsigned char do_crc8(unsigned char b, unsigned char crc);
	virtual unsigned char  performCRCcalculation() = 0;
	public:
	WakePacket(const ISerial &wakeUpSerial):_wakeUpSerial(wakeUpSerial) {}
	virtual ~WakePacket() {}
	unsigned char getAddress() const {return _address;}
	unsigned char getCommand() const {return _command;}
	unsigned char getDataSize() const {return _dataSize;}
	const char* getData() const {return _data;}
};


#endif /* WAKEPACKET_H_ */