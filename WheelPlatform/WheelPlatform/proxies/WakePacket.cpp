#include "WakeUpSerial.h"

unsigned char WakePacket::do_crc8(unsigned char b, unsigned char crc) {
	unsigned char i;
	for (i = 0; i < 8; b = b >> 1, i++) {
		if (((b ^ crc) & 1) == 1) {
			crc = ((crc ^ 0x18) >> 1) | 0x80;
			} else {
			crc = (crc >> 1) & 0x7F;
		}
	}
	return crc;
}
