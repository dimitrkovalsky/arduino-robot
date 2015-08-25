#include "WakeUpSerial.h"
#include "Print.h"
//void alarm();// ???????

WakePacketRx* WakeUpSerial::createRxPacket() const {
	return new WakePacketRx(*this);
}

WakePacketTx* WakeUpSerial::createTxPacket(unsigned char address, unsigned char command, const char *data, unsigned char dataSize) const {
	return new WakePacketTx(*this, address, command, data, dataSize);
}

void WakeUpSerial::processing() {
	if(_wakePacketReceived) {
		wakePacketReceived(_rxWakePacket); // processing RX wakePacket
		delete _rxWakePacket;
		_rxWakePacket = this->createRxPacket();
		_wakePacketReceived = false;
	}
}

void WakeUpSerial::keepRxOn() {
	while (_serial.available() && !_wakePacketReceived) {
		_wakePacketReceived = _rxWakePacket->read();
	}
}

void WakeUpSerial::wakePacketReceived(const WakePacketRx* rxp) {

	if (rxp->getCodeErr() == ERR_NO && rxp->getAddress() == GetWakeAddress()) {
		switch (rxp->getCommand()) {
			case CMD_NOP :
			break;
			case CMD_ECHO :
				sendAnswer(rxp,  rxp->getData(), rxp->getDataSize());
			break;
			default:
				if(_listener) {
					_listener(this, rxp);
				}
				else if(m_callback){
					ReciveEventArgs* args = new ReciveEventArgs(rxp);
					(*m_callback)(this, args);
				}
			break;
		}
	}
}

void WakeUpSerial::sendAnswer(const WakePacketRx* rxp, const char* data,  size_t dataSize) const {
	WakePacketTx* txp = this->createTxPacket(rxp->getAddress(), rxp->getCommand() | MOD_ANSW, data, (unsigned char)dataSize);
	txp->send();
	delete txp;
}
