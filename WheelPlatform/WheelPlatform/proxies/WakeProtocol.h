#ifndef WAKEPROTOCOLCONSTANTS_H_
#define WAKEPROTOCOLCONSTANTS_H_

#define SLIPFRAME     100   //packet max long

// protocol WAKE

//Universal command code:

#define CMD_NOP  0    //nop
#define CMD_ERR  1    //rx packet error
#define CMD_ECHO 2    //send echo
#define CMD_INFO 3    //send device info

#define MOD_ANSW  0x40 // command modifier for answer

//Error code:

#define ERR_NO 0x00   //no error
#define ERR_TX 0x01   //Rx/Tx error
#define ERR_BU 0x02   //device busy error
#define ERR_RE 0x03   //device not ready error
#define ERR_PA 0x04   //parameters value error
#define ERR_NR 0x05   //no replay
#define ERR_NC 0x06   //no carrier


#endif /* WAKEPROTOCOLCONSTANTS_H_ */