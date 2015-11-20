
#ifndef STAR_PACKET_H_
#define STAR_PACKET_H_

#include <cstdint>

class StarPacket{
    public:
		StarPacket(){};
		uint8_t getXid(){ return xid; }
    protected:
		uint8_t xid;
};

#endif
