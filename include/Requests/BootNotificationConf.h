#pragma once

#include "Device.h"
#include "States/Available.h"
#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"

class BootNotificationConf : public AbstractHandler {
    public:

        const char * Payload_key = "$[2]";
        string currentTime;
        int interval;
        RegistrationStatus status;
        string & Handle(std::string & payload) override;
};

