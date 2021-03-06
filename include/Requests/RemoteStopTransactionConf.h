#pragma once
#include <Arduino.h>
#include "Types/Types.h"
extern "C" {
  #include "mjson.h"
}
#include "Requests/AbstractHandler.h"
#include "OCPP_Client.h"

class RemoteStopTransactionConf : public AbstractHandler {
    public:
        RemoteStopTransactionConf() {}
        /* response example
        * {"status": "Accepted"}
        */
        RemoteStartStopStatus status_;
        const char * payload_format = "{%Q: %Q}";
        void SetPayload(string & payload);
        void SetStatus(RemoteStartStopStatus status);
        Msg Handle(Msg & msg) override;
};