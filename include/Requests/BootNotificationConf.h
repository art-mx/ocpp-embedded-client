#pragma once
#include "Requests/Message.h"
// #include "States/Operational.h"

class BootNotificationConf : public Message {
    public:
        string currentTime;
        int interval;
        RegistrationStatus status;
        void MessageHandler(std::string & payload);
};

