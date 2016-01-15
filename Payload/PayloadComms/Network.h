
class Network{
    public:
		Network(uint32_t ip,uint8_t port);
		void SendPacket(uint32_t packet);
    private:
		ServerWorker();
		ClientWorker();
		uint32_t myIP, uint8_t myPort;	
		uint32_t mySendPacket;
};
