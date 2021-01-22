#pragma once
#include "Requests/CallResult.h"
#include "Device.h"
#include "States/Available.h"

class BootNotificationConf : public CallResult {
    public:
        // BootNotificationConf(CallResult const& c) : CallResult(c) {}
        // BootNotificationConf() {}
        string currentTime;
        int interval;
        RegistrationStatus status;
        void MessageHandler(std::string & payload, Device * device);
};

