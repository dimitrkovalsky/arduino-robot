#ifndef __RECIVEEVENTHANDLER_H__
#define __RECIVEEVENTHANDLER_H__

#include "WakeUpSerial.h"
#include "BaseReciveEventHandler.h"
#include "ReciveEventArgs.h"

template <class TClass> class ReciveEventHandler : public BaseReciveEventHandler
{
	private:
	typedef void (TClass::*CallbackDelegate)(const Object* sender, const ReciveEventArgs* args);
	TClass* m_obj;
	CallbackDelegate m_callback;

	public:

	ReciveEventHandler( TClass* obj, CallbackDelegate callback ){
		m_callback = callback;
		m_obj = obj;
	};

	virtual void operator()(const Object* sender, const ReciveEventArgs* args){
		(*m_obj.*m_callback)(sender, args);
	}
};

#endif
