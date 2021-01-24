#include "Requests/ChangeAvailabilityReq.h"
#include "Requests/ChangeAvailabilityConf.h"

Msg ChangeAvailabilityReq::Handle(Msg & msg) { //TODO change payload to OBJECT
    int connectorId;
    string availability_str;
    AvailabilityType availability;

    if (!GetInteger(msg.payload, "$.connectorId", &connectorId)){
        logser.printf("'connectorId' key not found in payload %s\r\n", msg.payload.c_str());
        return msg;
    }
    if (!GetString(msg.payload, "$.type", availability_str)) {
        logser.printf("'type' key not found in payload %s\r\n", msg.payload.c_str());
        return msg;
    }

    availability = AvailabilityTypeNamesMap[availability_str];
    AvailabilityStatus status = this->device_->state_->StateHandle_AvailabilityStatus(availability);
    this->SetNext(new ChangeAvailabilityConf(status));
    return AbstractHandler::Handle(msg);
    
}