
#ifndef STAR_PACKET_0x01_H_
#define STAR_PACKET_0x01_H_

#include "StarPacket.h"

class StarPacket0x01 : public StarPacket{
    public:
		StarPacket0x01();
    private:
};

StarPacket0x01::StarPacket0x01(){
	xid=1;
}

#endif
