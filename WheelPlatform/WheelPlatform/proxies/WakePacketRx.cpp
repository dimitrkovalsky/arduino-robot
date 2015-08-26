#include "WakePacketRx.h"

bool WakePacketRx::read() {
	
	int rxb = _wakeUpSerial.read();

	if (rxb == -1) return false;
	unsigned char rb = (unsigned char)rxb;
	if (rb == FEND)  _state = rxBEGIN;
	if(rb == FESC && _flagFESC == false) {
		_flagFESC = true;
		return false;
	}
	if (_flagFESC == true) { //byte stuffing
		_flagFESC = false;
		if (rb == TFEND) rb = FEND;
		else if (rb == TFESC) rb = FESC;
	}

	switch(_state) {
		case  rxBEGIN:
			if(rb == FEND) {
				_state = rxSTARTPACKET;
			}
		break;
		case rxSTARTPACKET:
			if(rb & 0x80) {
				_state = rxADDRESS;
				_address = rb & 0x7F;
				_rxAddressIsPresent = true;
			} else {
				_state = rxCOMMAND;
				_address = 0;
				_command = rb;
			}
		break;
		case rxADDRESS:
			_state = rxCOMMAND;
			_command = rb;
		break;
		case rxCOMMAND: // receive CntData
			_dataptr = _data;
			_state = (rb != 0) ? rxDATA : rxCRC;
			_dataSize = rb;
			if(rb > SLIPFRAME) {// err: packet is very long
				_codeErr = ERR_TX;
				return true;
			}
		break;
		case rxDATA:
			*_dataptr++ = rb;
			if((_dataptr - _data) == _dataSize) {
				_state = rxCRC;
			}
		break;
		case rxCRC: {
			_codeErr = (rb == this->performCRCcalculation()) ? ERR_NO : ERR_TX;
			return true;
		}
	}
	
	return false;
}

unsigned char WakePacketRx::performCRCcalculation() {
	unsigned char crc = CRC_INIT;
	crc = do_crc8(FEND, crc);
	if (_rxAddressIsPresent) crc = do_crc8(this->getAddress(), crc);
	crc = do_crc8(this->getCommand(), crc);
	unsigned char i = this->getDataSize();
	crc = do_crc8(i, crc);
	const char *data = this->getData();
	while (i--) {
		crc = do_crc8(*data++, crc);
	}
	return crc;
}