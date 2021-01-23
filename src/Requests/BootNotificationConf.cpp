#include "Requests/BootNotificationConf.h"

string & BootNotificationConf::Handle(std::string & msg) {
    string status_str;
    string payload;

    if(!GetObject(msg, Payload_key, payload)) {
        logser.println("cannot find payload object");
        return msg;
    }

    if(!GetString(payload, "$.status", status_str)) {
        logser.println("cannot find 'status' key in payload");
        return msg;
    }
    status = RegistrationStatusMap[status_str];
    switch (status) {
        case ACCEPTED:
            logser.println("got ACCEPTED RegistrationStatus");
            device_->state_->HandleRegistrationStatusAccepted();
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
    return msg;
}   