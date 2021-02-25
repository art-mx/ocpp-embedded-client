#pragma once
#include <Arduino.h>
#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"
#include "Device.h"
#include "States/State.h"
#include "OCPP_Client.h"

class RemoteStartTransactionConf;

class RemoteStartTransactionReq: public AbstractHandler {
    public:
        RemoteStartTransactionReq();
        Msg Handle(Msg & msg) override;
    private:
        RemoteStartTransactionConf * RemoteStartTransactionConf_;
};
