#pragma once
#include <Arduino.h>
#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"
#include "Device.h"
#include "States/State.h"
#include "OCPP_Client.h"

class RemoteStopTransactionConf;
class StopTransactionReq;

class RemoteStopTransactionReq: public AbstractHandler {
    public:
        RemoteStopTransactionReq();
        Msg Handle(Msg & msg) override;
    private:
        RemoteStopTransactionConf * RemoteStopTransactionConf_;
        StopTransactionReq * StopTransactionReq_; 
};
