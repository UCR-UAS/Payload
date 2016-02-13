#ifndef PAYLOAD_STATUS_H
#define PAYLOAD_STATUS_H
#include <cstdint>

/*! 
 PayloadStatus Packet Class Definition
*/
class PayloadStatus
{
    private:
    uint32_t packet;
    
    public:
    PayloadStatus();
    //uint32_t getPacket() {return packet;} //for testing
    void setPacket(uint32_t newPacket);
    //Bits 0 - 7 represent asterisk character 
    void setConnectivityBit(bool x); //Bit 8
    bool getConnectivityBit();
    //bits 9 -16
    void setCaptureBit(bool x); //Bit 17
    bool getCaptureBit();
    void setTransmissionBit(bool x); //Bit 18
    bool getTransmissionBit();
    void setADLCBit(bool x); //Bit 19
    bool getADLCBit();
    //Bits 20 - 31
};

#endif //PAYLOAD_STATUS_H
