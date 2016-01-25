#include <iostream>
#include "PayloadStatus.h"
using namespace std;
int main() {
    PayloadStatus swege;
	
	//swege.setPacket(0xFF); For testing setPacket
	//cout << swege.getPacket() << endl;
	swege.setConnectivityBit(0);
    cout << swege.getConnectivityBit() << endl;
    swege.setConnectivityBit(1);
	cout << swege.getConnectivityBit() << endl;
	
	swege.setConnectivityBit(0);
    cout << swege.getConnectivityBit() << endl;
    swege.setConnectivityBit(1);
    cout << swege.getConnectivityBit() << endl;
    
	swege.setCaptureBit(0);
    cout << swege.getCaptureBit() << endl;
    swege.setCaptureBit(1);
    cout << swege.getCaptureBit() << endl;
    
	swege.setADLCBit(0);
    cout << swege.getADLCBit() << endl;
    swege.setADLCBit(1);
    cout << swege.getADLCBit() << endl;
    
	swege.setTransmissionBit(0);
    cout << swege.getTransmissionBit() << endl;
    swege.setTransmissionBit(1);
    cout << swege.getTransmissionBit() << endl;
    
    return 0;
}