
#include <iostream>
#include "../../Resources/PayloadStatus.h"

class PayloadGUIExec{
	public:
		PayloadGUIExec(PayloadStatus* payload_status);
	private:
		PayloadStatus *myPayloadStatus;
};
