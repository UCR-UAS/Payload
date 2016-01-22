#ifndef STARPACKET0X02_H
#define STARPACKET0X02_H
#include <cstdint>
class StarPacket0x02
{
    private:
    uint32_t packet;
    
    public:
    StarPacket0x02();
    //Bits 0 - 7 represent asterisk character 
    void setConnectivityBit(bool x); //Bit 8
    bool getConnectivityBit();
    void setPingServerBit(bool x); // Bit 9
    bool getPingServerBit();
    void setNetworkBit(bool x); //Bit 10
    bool getNetworkBit();
    //bits 11- 13
    void setCaptureBit(bool x); //Bit 14
    bool getCaptureBit();
    void setNamingBit(bool x); //Bit 15
    bool getNamingBit();
    void setADLCBit(bool x); //Bit 16
    bool getADLCBit();
    void setTransmissionBit(bool x); //Bit 17
    bool getTransmissionBit();
    //Bits 18 - 31
};

#endif //STARPACKET0X02_H