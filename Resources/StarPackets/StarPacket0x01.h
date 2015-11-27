
#ifndef STAR_PACKET_0x01_H_
#define STAR_PACKET_0x01_H_

#include "StarPacket.h"

class StarPacket0x01 : public StarPacket{
    public:
		StarPacket0x01();
    private:
		uint32_t data;
};

StarPacket0x01::StarPacket0x01(){
	xid=1;
	data=0x2A;
}
//For the funcitons below, "set" is a bool, so it MUST be 0 or 1 when passed in.
//0 will always mean "turn off," while 1 means "turn on."

//Connects/disconnects to/from BaseStation (bit 8)
void setConnect(bool set) {set=1 ? data | 0x100 : data & 0xFFFFFEFF;}

// (bit 9)
void setPing(bool set) {set=1 ? data | 0x200 : data & 0xFFFFFDFF;}

// (bit 10)
void setNetwork(bool set) {set=1 ? data | 0x400 : data & 0xFFFFFBFF;}

// (bit 11)
void set???(bool set) {set=1 ? data | 0x800 : data & 0xFFFFF7FF;}

// (bit 12)
void set???(bool set) {set=1 ? data | 0x1000 : data & 0xFFFFEFFF;}

// (bit 13)
void set???(bool set) {set=1 ? data | 0x2000 : data & 0xFFFFDFFF;}

//Turns the camera capture on or off (bit 14)
void setCameraCapture(bool set) {set=1 ? data | 0x4000 : data & 0xFFFFBFFF;} 

//Starts and stops naming pictures (bit 15)
void setPictureNaming(bool set) {set=1 ? data | 0x8000 : data & 0xFFFF7FFF;}

//Starts and stops ADLC algorithm (bit 16)
void setADLC(bool set) {set=1 ? data | 0x10000 : data & 0xFFFEFFFF;}

//Stats and stops image transmission (bit 17)
void setImageTransmission(bool set) {set=1 ? data | 0x20000 : data & 0xFFFDFFFF;}

// (bit 18)
void set???(bool set) {set=1 ? data | 0x40000 : data & 0xFFFBFFFF;}

// (bit 19)
void set???(bool set) {set=1 ? data | 0x80000 : data & 0xFFF7FFFF;}

// (bit 20)
void set???(bool set) {set=1 ? data | 0x100000 : data & 0xFFEFFFFF;}

// (bit 21)
void set???(bool set) {set=1 ? data | 0x200000 : data & 0xFFDFFFFF;}

// (bit 22)
void set???(bool set) {set=1 ? data | 0x400000 : data & 0xFFBFFFFF;}

// (bit 23)
void set???(bool set) {set=1 ? data | 0x800000 : data & 0xFF7FFFFF;}

// (bit 24)
void set???(bool set) {set=1 ? data | 0x1000000 : data & 0xFEFFFFFF;}

// (bit 25)
void set???(bool set) {set=1 ? data | 0x2000000 : data & 0xFDFFFFFF;}

// (bit 26)
void set???(bool set) {set=1 ? data | 0x4000000 : data & 0xFBFFFFFF;}

// (bit 27)
void set???(bool set) {set=1 ? data | 0x8000000 : data & 0xF7FFFFFF;}

// (bit 28)
void set???(bool set) {set=1 ? data | 0x10000000 : data & 0xEFFFFFFF;}

// (bit 29)
void set???(bool set) {set=1 ? data | 0x20000000 : data & 0xDFFFFFFF;}

// (bit 30)
void set???(bool set) {set=1 ? data | 0x40000000 : data & 0xBFFFFFFF;}

// (bit 31)
void set???(bool set) {set=1 ? data | 0x80000000: data & 0x7FFFFFFF;}

#endif
