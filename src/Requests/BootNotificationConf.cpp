#include "Requests/BootNotificationConf.h"
#include "rtc.h"


Msg BootNotificationConf::Handle(Msg & msg) {

    string currentTime;
    if(!GetString(msg.payload, "$.currentTime", currentTime)) {
        logser.printf("'currentTime' key not found in payload %s\r\n", msg.payload.c_str());
        return msg;
    }
    adjust_rtc(currentTime);

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