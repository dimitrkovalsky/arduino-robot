#ifndef SLIPCONSTANTS_H_
#define SLIPCONSTANTS_H_

//SLIP protocol

#define 	FEND		(unsigned char)0xC0 // Frame End
#define 	FESC 		(unsigned char)0xDB // Frame Escape
#define 	TFEND		(unsigned char)0xDC // Transposed Frame End
#define 	TFESC		(unsigned char)0xDD // Transposed Frame Escape

#define 	CRC_INIT  0xDE  //initial CRC value

#endif /* SLIPCONSTANTS_H_ */