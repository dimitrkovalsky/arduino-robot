#include "Parser.h"

unsigned char Parser::OneSymbolToByte(char Symbol, bool* An_error_has_occured_POINTER){
	
	switch( Symbol )
	{
		case '0' : return 0;
		case '1' : return 1;
		case '2' : return 2;
		case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
		case '7' : return 7;
		case '8' : return 8;
		case '9' : return 9;
		
		default :
		* An_error_has_occured_POINTER = true;  // Error
		return 0;  // Error
	}
}

unsigned char Parser::TwoSymbolsToByte(char twoBytes[2], bool* An_error_has_occured_POINTER){

	return 10 * OneSymbolToByte( twoBytes[0], An_error_has_occured_POINTER ) +
				OneSymbolToByte( twoBytes[1], An_error_has_occured_POINTER );
}

unsigned char Parser::TwoSymbolsToByte(char first, char second, bool* An_error_has_occured_POINTER)
{
	return 10 * OneSymbolToByte( first, An_error_has_occured_POINTER ) +
	OneSymbolToByte( second, An_error_has_occured_POINTER );
}