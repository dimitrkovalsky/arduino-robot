#include "RemoteClimateDevice.h"

//int deviceAddress = 0;

WakeUpSerial wakeUpSerial(Serial, 9600);


void setup() {
  Serial.println("starting WakeUp ...");
  wakeUpSerial.addRxPacketListener(RemoteClimateDevice::wakeUpRxHandler);
}

void loop() {
  wakeUpSerial.processing();
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  wakeUpSerial.keepRxOn();
}


