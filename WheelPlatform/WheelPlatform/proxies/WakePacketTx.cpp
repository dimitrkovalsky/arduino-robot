#include "WakePacketTx.h"

WakePacketTx::WakePacketTx(
	const ISerial &wakeUpSerial,
	unsigned char address,
	unsigned char command,
	const char *data,
	unsigned char dataSize
	): WakePacket(wakeUpSerial), _sendAddress(true) {
	
	_address = address;
	_command = command;
	_data = new char[dataSize+1];
	memcpy((char*)_data, (char*)data, (size_t)dataSize);
	_dataSize = dataSize;
}

WakePacketTx::WakePacketTx(
	const ISerial &wakeUpSerial,
	unsigned char command,
	const unsigned char *data,
	unsigned char dataSize
	) : WakePacket(wakeUpSerial), _sendAddress(false) {

	_command = command;
	_data = new char[dataSize+1];
	memcpy((char*)_data, (char*)data, (size_t)dataSize);
	_dataSize = dataSize;
}

unsigned char WakePacketTx::performCRCcalculation() {
	unsigned char crc = CRC_INIT;
	crc = do_crc8(FEND, crc);
	if (_sendAddress) crc = do_crc8(this->getAddress(), crc);
	crc = do_crc8(this->getCommand(), crc);
	unsigned char i = this->getDataSize();
	crc = do_crc8(i, crc);
	const char *data = this->getData();
	while (i--) {
		crc = do_crc8(*data++, crc);
	}
	return crc;
}

void WakePacketTx::sendStartSLIP() {
	_wakeUpSerial.write(FEND);
}

void WakePacketTx::sendCharSLIP(unsigned char val) {
	if(val == FEND) {
		_wakeUpSerial.write(FESC);
		_wakeUpSerial.write(TFEND);
	}
	else if (val == FESC) {
		_wakeUpSerial.write(FESC);
		_wakeUpSerial.write(TFESC);
	}
	else {
		_wakeUpSerial.write(val);
	}
}

void  WakePacketTx::send() {
	sendStartSLIP(); // start packet
	if(_sendAddress) sendCharSLIP(this->getAddress() | 0x80); // send address
	sendCharSLIP(this->getCommand()); // send command
	unsigned char i = this->getDataSize();
	sendCharSLIP(i); // send dataSize
	const char *data = this->getData();
	while(i--) {
		sendCharSLIP(*data++); // send data byte
	}
	sendCharSLIP(performCRCcalculation()); // send crc
}
