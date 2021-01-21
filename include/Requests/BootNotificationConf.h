#pragma once
#include "Requests/Message.h"
#include "Device.h"
#include "States/Available.h"

class BootNotificationConf : public Message {
    public:
        string currentTime;
        int interval;
        RegistrationStatus status;
        void MessageHandler(std::string & payload, Device * device);
};

