#include "PayloadStatus.h"
//! SetBit Function is Used to set a specific bit of the packet
//! x is the number to edit
//! k selects the bit (0 - 31)
//! b is what to set the bit to (1 or 0)
uint32_t SetBit(uint32_t x, unsigned char k, bool b) {
	if(b) {
	    return ( x | (0x01 << k) );
	}
	else {
	    return ( x & ~(0x01 << k) );
	}
}
//! GetBit Function is used to get a specific bit of the packet
//! x is the number to check
//! k is the bit to report within x
bool GetBit(uint32_t x, unsigned char k) {
	return ( x & (0x01 << k) ) != 0;
}

//! Packet initialized to asterisk
PayloadStatus::PayloadStatus() {
    packet = 0x0002A; //asterisk = 0x2A
}

void PayloadStatus::setPacket(uint32_t newPacket) {
	packet = newPacket;
}

void PayloadStatus::setConnectivityBit(bool x) {
    if(x) {
        packet = SetBit(packet, 8, 1);
    }
    else {
        packet = SetBit(packet, 8, 0);
    }
}
bool PayloadStatus::getConnectivityBit() {
    return GetBit(packet, 8);
}

void PayloadStatus::setTransmissionBit(bool x) {
    if(x) {
        packet = SetBit(packet, 17, 1);
    }
    else {
        packet = SetBit(packet, 17, 0);
    }
}
bool PayloadStatus::getTransmissionBit() {
    return GetBit(packet, 17);
}

void PayloadStatus::setCaptureBit(bool x) {
    if(x) {
        packet = SetBit(packet, 18, 1);
    }
    else {
        packet = SetBit(packet, 18, 0);
    }
}
bool PayloadStatus::getCaptureBit() {
    return GetBit(packet, 18);
}

void PayloadStatus::setADLCBit(bool x) {
    if(x) {
        packet = SetBit(packet, 19, 1);
    }
    else {
        packet = SetBit(packet, 19, 0);
    }
}
bool PayloadStatus::getADLCBit() {
    return GetBit(packet, 19);
}
