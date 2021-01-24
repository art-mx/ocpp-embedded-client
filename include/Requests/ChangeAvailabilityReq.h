#pragma once
#include <Arduino.h>
#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"
#include "Device.h"
#include "States/State.h"
#include "OCPP_Client.h"
// class Device;

class ChangeAvailabilityReq: public AbstractHandler {
    public:
        Msg Handle(Msg & msg) override;
};
