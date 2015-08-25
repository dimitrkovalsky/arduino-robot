#ifndef __WAKEPACKETTX_H__
#define __WAKEPACKETTX_H__

#include "WakePacket.h"
#include "SLIPProtocol.h"

class WakePacketTx: public WakePacket {
	private:
	unsigned char  performCRCcalculation();
	boolean _sendAddress;
	void sendStartSLIP();
	void sendCharSLIP(unsigned char val);
	public:

	WakePacketTx(
		const ISerial &wakeUpSerial,
		unsigned char command,
		const unsigned char *data,
		unsigned char dataSize
	);

	WakePacketTx(
		const ISerial &wakeUpSerial,
		unsigned char adress,
		unsigned char command,
		const char *data,
		unsigned char dataSize
	);

	~WakePacketTx() {delete [] _data;}
	void send();
};

#endif //__WAKEPACKETTX_H__
