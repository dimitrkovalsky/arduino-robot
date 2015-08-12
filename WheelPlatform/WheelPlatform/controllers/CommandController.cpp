#include "CommandController.h"

void CommandController::Setup(){
	Serial.begin( 9600 );

	RadioCar.Setup();
	Hand.Setup();
}

void CommandController::Loop(){

	//Hand.Log();
	
	if ( Serial.available() > 0 ){
		
		Comand_bytes_array[m_size] = Serial.read();
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
			Serial.write("Got wheels command");
		break;
		case 'H':
			Hand.Execute( Comand_bytes_array );
			Serial.write("Got hands command");
		break;
		default:
		* error = true;
		break;
	}
}


