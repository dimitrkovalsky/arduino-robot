#include "CommandController.h"

void CommandController::Setup(){
	Serial.begin( 9600 );

	RadioCar.Setup();
	Hand.Setup();
}

void CommandController::Loop(){

	//Hand.Log();

	while ( Serial.available() > 0 ){
		
		int cmdPart = Serial.read();

		//if(m_size == 0 && (cmdPart != 'M' || cmdPart != 'W')){
			//return;
		//}

		Comand_bytes_array[m_size] = cmdPart;
		m_size++;
		
		if( m_size == COMMAND_SIZE ){
			m_size = 0;
			ExecuteCommand(	&HasError );
		}
	}
}

void CommandController::ExecuteCommand( bool* error ){
	
	switch (Comand_bytes_array[0]){
		case 'W':
		RadioCar.Execute( Comand_bytes_array );
		break;
		case 'M':
		Hand.Execute( Comand_bytes_array );
		break;
		default:
		* error = true;
		break;
	}
}


