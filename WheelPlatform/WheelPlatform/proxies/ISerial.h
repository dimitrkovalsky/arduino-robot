#ifndef __ISERIAL_H__
#define __ISERIAL_H__


class ISerial
{
//functions
public:
	virtual int read() const = 0;
	virtual void write(unsigned char ch) const = 0;

}; //ISerial

#endif //__ISERIAL_H__
