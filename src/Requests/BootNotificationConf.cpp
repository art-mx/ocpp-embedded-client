#include "Requests/BootNotificationConf.h"

Msg BootNotificationConf::Handle(Msg & msg) {

    string currentTime;
    GetString(msg.payload, "$.currentTime", currentTime); //TODO

    int interval;
    GetInteger(msg.payload, "$.interval", &interval); //TODO
        
    string status_str;
    if(!GetString(msg.payload, "$.status", status_str)) {
        logser.println("cannot find 'status' key in payload");
        return msg;
    }
    RegistrationStatus status = RegistrationStatusMap[status_str];
    device_->state_->StateHandle_RegistrationStatus(status);

    return msg;
}   