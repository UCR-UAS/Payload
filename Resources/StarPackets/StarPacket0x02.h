
#ifndef STAR_PACKET_0x02_H_
#define STAR_PACKET_0x02_H_

#include "StarPacket.h"

class StarPacket0x02 : public StarPacket{
    public:
		StarPacket0x02();
    private:
		uint32_t data;
};

StarPacket0x02::StarPacket0x02(){
	xid=2;
	data = 0x2A;
}

//Question/potential problem. These functions should not modify the status packet, but returning "data & 0x100" also sets "data" equal to the result that is computed doesn't it? So maybe "data should be duplicated, then the function could just use the bitwise operation on that duplicate and return the result. If this is correct, I will alter the functions.

//Gets status of connection to BaseStation (bit 8)
bool getConnect() { return data & 0x100;}

//Gets status of whether pinging server or not (bit 9)
bool getPing() {return data & 0x200 ;}

//Gets status of whether connected or not (bit 10)
bool getNetwork () {return data & 0x400 ;}

// (bit 11)
bool get () {return data & 0x800 ;}

// (bit 12)
bool get () {return data & 0x1000 ;}

// (bit 13)
bool get () {return data & 0x2000 ;}

//Gets status of camera capture (bit 14)
bool getCameraCapture() { return data & 0x4000;}

//Gets status of whether naming pictures or not (bit 15)
bool getPictureNaming () {return data & 0x8000 ;}

//Tells if ADLC is on or not (bit 16)
bool getADLC () {return data & 0x10000 ;}

//Tells if currently sending images or not (bit 17)
bool getImageTransmission () {return data & 0x20000 ;}

// (bit 18)
bool get () {return data & 0x40000 ;}

// (bit 19)
bool get () {return data & 0x80000 ;}

// (bit 20)
bool get () {return data & 0x100000 ;}

// (bit 21)
bool get () {return data & 0x200000 ;}

// (bit 22)
bool get () {return data & 0x400000 ;}

// (bit 23)
bool get () {return data & 0x800000 ;}

// (bit 24)
bool get () {return data & 0x1000000 ;}

// (bit 25)
bool get () {return data & 0x2000000 ;}

// (bit 26)
bool get () {return data & 0x4000000 ;}

// (bit 27)
bool get () {return data & 0x8000000 ;}

// (bit 28)
bool get () {return data & 0x10000000 ;}

// (bit 29)
bool get () {return data & 0x20000000 ;}

// (bit 30)
bool get () {return data & 0x40000000 ;}

// (bit 31)
bool get () {return data & 0x80000000 ;}

#endif
