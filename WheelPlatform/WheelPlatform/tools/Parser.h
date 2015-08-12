#ifndef __PARSER_H__
#define __PARSER_H__

class Parser
{

public:
static unsigned char TwoSymbolsToByte(
		char twoBytes[2],
		bool* An_error_has_occured_POINTER
	);

private:
static unsigned char OneSymbolToByte( char Symbol, bool* An_error_has_occured_POINTER );

};

#endif
