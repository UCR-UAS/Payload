
#include <iostream>
#include "StarPacket.h"
#include "StarPacket0x01.h"
#include "StarPacket0x02.h"
#include "StarPacket0x03.h"

using namespace std;

int main(){
	StarPacket0x01 sp1;
	StarPacket0x02 sp2;
	StarPacket0x03 sp3;
	StarPacket* list[3];
	list[0]=(StarPacket*)&sp1;
	list[1]=(StarPacket*)&sp2;
	list[2]=(StarPacket*)&sp3;

	for(int i=0;i<3;++i){
		cout<<(int)list[i]->getXid()<<endl;
	}
	return 0;
}
