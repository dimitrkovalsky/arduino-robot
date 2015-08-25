#ifndef BASERECIVEEVENTHANDLER_H_
#define BASERECIVEEVENTHANDLER_H_

#include "WakeUpSerial.h"
#include "ReciveEventArgs.h"
#include "core/Object.h"

class BaseReciveEventHandler
{
public:
	virtual void operator()(const Object* sender, const ReciveEventArgs* args){}
};

#endif