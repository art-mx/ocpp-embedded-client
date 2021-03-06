#pragma once
#include <Arduino.h>
#include "Types/Types.h"
#include "Requests/AbstractHandler.h"

extern "C" {
  #include "mjson.h"
}
#include <string>
using std::string;

class StopTransactionReq{

    public:
        string Payload(int meterStop, string timestamp, int transactionId, StopTransactionReason reason);
        const string Action = "StopTransaction";
        /*
        * {"meterStop": 1234, "timestamp": "2021-02-25T13:01:23.684Z", "transactionId": 1234, "reason": "Local"}
        */
        const char * payload_format = "{%Q:%d, %Q:%Q, %Q:%d, %Q:%Q}";

};