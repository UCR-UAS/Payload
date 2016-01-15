

Network::Network(uint32_t ip,uint8_t port):
	myIP(ip),
	myPort(port)
{
	mySendPacket=0;
}

void Network::SendPacket(uint32_t packet){
	mySendPacket=packet;
}
