#include "Requests/BootNotificationConf.h"

void BootNotificationConf::MessageHandler(std::string & payload, Device * device) {
    string status_str;
    if(!GetString(payload, "$.status", status_str)) {
        logser.println("cannot find 'status' key in payload");
        return;
    }
    status = RegistrationStatusMap[status_str];
    switch (status) {
        case ACCEPTED:
            logser.println("got ACCEPTED RegistrationStatus");
            // device->state_->HandleRegistrationStatusAccepted();
            // handle this
            break;
        case PENDING:
            logser.println("got PENDING RegistrationStatus");
            // handle this
            break;
        case REJECTED:
            logser.println("got REJECTED RegistrationStatus");
            // handle this
            break;
        case UNDEFINED:
            logser.println("got UNDEFINED RegistrationStatus");
            break;
        default:
            logser.println("unknown value for RegistrationStatus");
    }
    GetString(payload, "$.currentTime", currentTime);
    GetInteger(payload, "$.interval", &interval);
    
}   