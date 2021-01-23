#pragma once
// #include "Requests/CallResult.h"
#include "Device.h"
#include "States/Available.h"
#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"

class BootNotificationConf : public AbstractHandler {
    public:
        // BootNotificationConf(CallResult const& c) : CallResult(c) {}
        // BootNotificationConf();
        string currentTime;
        int interval;
        RegistrationStatus status;
        void MessageHandler(std::string & payload, Device * device);
};

