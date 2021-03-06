#pragma once

#include <Arduino.h>
#include <vector>
//#include <map>
#include <memory>
#include "Types/Types.h"
#include "Requests/AbstractHandler.h"
#include "JSONParser.h"
#include "Device.h"

class ChangeAvailabilityReq;
class RemoteStartTransactionReq;
class RemoteStopTransactionReq;

using namespace std;
#define MAX_CALL_NUM 10 // number of calls to store

extern HardwareSerial logser;

class Call : public AbstractHandler {
    public:
        Call();

        Msg Handle(Msg & msg) override;
        /*
        * [<MessageTypeId>, "<UniqueId>", "<Action>", {<Payload>}]
        */
        const char * format = "[%d, %Q, %Q, %s]\n";
        const char * MessageTypeId_key = "$[0]";
        const char * UniqueId_key = "$[1]";
        const char * Action_key = "$[2]";
        const char * Payload_key = "$[3]";


        string GenerateUniqueId() {
            static int i = 0;
            ++i;
            return to_string(i);
        }
    private:
        ChangeAvailabilityReq * ChangeAvailabilityReq_;
        RemoteStartTransactionReq * RemoteStartTransactionReq_;
        RemoteStopTransactionReq * RemoteStopTransactionReq_;
};


