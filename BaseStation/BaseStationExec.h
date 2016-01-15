#ifndef _BASE_STATION_EXEC_H
#define _BASE_STATION_EXEC_H

#include <iostream>
#include "../Resources/PayloadStatus.h"
#include "BaseStation/BaseStationCommsExec.h"
#include "BaseStation/PayloadGUIExec.h"

class BaseStationExec{
	public:
		BaseStationExec();
	private:
		PayloadStatus BSPayloadStatus;
		BaseStationCommsExec *BSCommsExec;
		PayloadGUIExec *BSGUIExec;
};

#endif
