#include "CommandController.h"

CommandController::CommandController(){

	ReciveEventHandler<CommandController>* handlerDelegate = new ReciveEventHandler<CommandController>(
		this,
		&CommandController::ReciveCommandHandler
	);

	m_wakeUpSerial = new WakeUpSerial(Serial, 9600);
	m_wakeUpSerial->addRxPacketListener(handlerDelegate);

	RadioCar.Setup();
	Hand.Setup();
}

void CommandController::ReciveCommandHandler(const Object* sender, const ReciveEventArgs* args){
	const WakePacketRx* rxp = args->GetPacket();
	WakePacketTx* txp;
	char err = ERR_PA;

	switch (rxp->getCommand()) {
		case 77 :{
			const char* recivedData = rxp->getData();
			Hand.Execute( recivedData );
			//m_wakeUpSerial->sendAnswer(rxp, recivedData, strlen(recivedData));
		}
		break;
		case 87 :
			RadioCar.Execute( rxp->getData() );
			//m_wakeUpSerial->sendAnswer(rxp, &err, 1);
		break;
		default:
			m_wakeUpSerial->sendAnswer(rxp, &err, 1);
		break;
	}

}
void CommandController::RaiseSerialReciveEvent(){
	m_wakeUpSerial->keepRxOn();
}

void CommandController::Loop(){
	m_wakeUpSerial->processing();
}