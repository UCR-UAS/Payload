
#ifndef _PAYLOADCOMMSEXEC_H
#define _PAYLOADCOMMSEXEC_H

#include "Network.h"

class PayloadCommsExec{
    public:
		PayloadCommsExec(PayloadStatus* payload_status);
    private:
		uint32_t myIp;
		uint8_t myPort;
		// Network object for sending packets
		Network BSNetwork(myIp,myPort);
		PacketFramer BSPacketFramer(&BSNetwork);
};

#endif
