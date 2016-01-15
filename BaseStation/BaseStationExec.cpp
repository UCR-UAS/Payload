
#include "BaseStationExec.h"

BaseStationExec::BaseStationExec(){
	BSCommsExec = new BaseStationCommsExec(&BSPayloadStatus);
	BSGUIExec = new PayloadGUIExec(&BSPayloadStatus);
}
