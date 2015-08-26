#ifndef __WAKEPACKETRX_H__
#define __WAKEPACKETRX_H__

#include "WakePacket.h"
#include "WakeProtocol.h"
#include "SLIPProtocol.h"

class WakePacketRx: public WakePacket {
	private:
	unsigned char  performCRCcalculation();
	// for receive logic :
	enum STATE_RX {
		rxBEGIN=0,
		rxSTARTPACKET,
		rxADDRESS,
		rxCOMMAND,
		rxDATA,
		rxCRC
	};
	unsigned char _codeErr = ERR_NO;
	bool _flagFESC = false; // for byte stuffing
	STATE_RX _state = rxBEGIN; // for receive state
	bool _rxAddressIsPresent = false;
	char* _dataptr;

	public:
	WakePacketRx(const ISerial &wakeUpSerial):WakePacket(wakeUpSerial) {
		_data = new char [SLIPFRAME];
	}
	
	~WakePacketRx() {delete [] _data;}

	bool read();
	unsigned char getCodeErr() const {return _codeErr;}
};

#endif //__WAKEPACKETRX_H__
