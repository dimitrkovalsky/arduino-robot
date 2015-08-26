#ifndef __RECIVEEVENTARGS_H__
#define __RECIVEEVENTARGS_H__

class ReciveEventArgs
{
private:
	const WakePacketRx* m_recivePacket;
public:
	ReciveEventArgs(const WakePacketRx* recivePacket){
		m_recivePacket = recivePacket;
	}

	const WakePacketRx* GetPacket() const { return m_recivePacket; }
};

#endif
