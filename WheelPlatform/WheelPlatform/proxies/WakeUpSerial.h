#ifndef WAKEUPSERIAL_H
#define WAKEUPSERIAL_H

#include "Arduino.h"
#include "SLIPProtocol.h"
#include "WakeProtocol.h"
#include "WakePacketTx.h"
#include "WakePacketRx.h"
#include "BaseReciveEventHandler.h"
#include "core/Object.h"
//#include "tests\wakeUpTest\Arduino.h"

//#define MultiDevice

#ifdef MultiDevice
extern unsigned char GetWakeAddress();
#else
static inline unsigned char GetWakeAddress() {return 1;}
#endif

typedef void (*RxPacketListener)(const Object* wserial, const WakePacketRx* rxp);

class WakeUpSerial : public Object, public ISerial{
	private:
	HardwareSerial& _serial;
	boolean _wakePacketReceived = false;
	WakePacketRx* _rxWakePacket = NULL;
	void wakePacketReceived(const WakePacketRx* rxp);
	RxPacketListener _listener = NULL;
	BaseReciveEventHandler* m_callback = NULL;
	public:

	WakeUpSerial(HardwareSerial &serial, unsigned long baud):_serial(serial) {
		_serial.begin(baud);
		_serial.println("starting WakeUp ...");
		_rxWakePacket = createRxPacket();
	}

	~WakeUpSerial() { if(_rxWakePacket) delete _rxWakePacket; }
	WakePacketRx* createRxPacket() const;
	WakePacketTx* createTxPacket(unsigned char address, unsigned char command, const char *data, unsigned char dataSize) const;
	void sendAnswer(const WakePacketRx* rxp, const char* data,  size_t dataSize) const;
	virtual int read() const {return _serial.read();}
	virtual void write(unsigned char ch) const { _serial.write(ch); }
	void processing(); // for calling in loop()
	void keepRxOn(); // for calling in serialEvent()
	void addRxPacketListener(RxPacketListener listener) { _listener = listener; }
	void addRxPacketListener(BaseReciveEventHandler* callback) { m_callback = callback; }
	void removeRxPacketListener() { 
		_listener = NULL; 
		m_callback = NULL;
	}
};


#endif
