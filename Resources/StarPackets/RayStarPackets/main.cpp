#include <iostream>
#include "StarPacket0x01.h"
using namespace std;
int main() {
    StarPacket0x01 swege;
    cout << swege.getConnectivityBit() << endl;
    swege.setConnectivityBit(1);
    cout << swege.getConnectivityBit() << endl;
    swege.setConnectivityBit(0);
    cout << swege.getConnectivityBit() << endl;
    
    cout << swege.getPingServerBit() << endl;
    swege.setPingServerBit(1);
    cout << swege.getPingServerBit() << endl;
    
    cout << swege.getNetworkBit() << endl;
    swege.setNetworkBit(1);
    cout << swege.getNetworkBit() << endl;
    
    cout << swege.getCaptureBit() << endl;
    swege.setCaptureBit(1);
    cout << swege.getCaptureBit() << endl;
    
    cout << swege.getNamingBit() << endl;
    swege.setNamingBit(1);
    cout << swege.getNamingBit() << endl;
    
    cout << swege.getADLCBit() << endl;
    swege.setADLCBit(1);
    cout << swege.getADLCBit() << endl;
    
    cout << swege.getTransmissionBit() << endl;
    swege.setTransmissionBit(1);
    cout << swege.getTransmissionBit() << endl;
    
    return 0;
}