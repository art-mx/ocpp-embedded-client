#pragma once
#include <Arduino.h>
using std::string;
#include "Types/Types.h"
#include "mjson.h"

class StatusNotificationReq {
    public:
        StatusNotificationReq() {};
        string Payload(int connector, string error, string status);
        /* required fields:
        * {"connectorId": <integer connectorId >= 0>, "errorCode": "<ChargePointErrorCode>", "status": "<ChargePointStatus>"} 
        */
       const char * payload_format = "{%Q: %d, %Q: %Q, %Q: %Q}\n";
       const string Action = "StatusNotification";


};