#pragma once

#include <Arduino.h>
#include <vector>
#include <map>
#include <memory>
#include "Types/Types.h"

using namespace std;

#define MAX_CALL_NUM 10 // number of calls to store

class PendingCall {
    public:
        PendingCall(string Action, string Payload);
        PendingCall();
        ~PendingCall() = default;
        const uint8_t MessageTypeId = MessageType::CALL;
        string Action;
        string UniqueId;
        string Payload;
        uint32_t timestamp_;
        int retries = 0;
        /*
        * [<MessageTypeId>, "<UniqueId>", "<Action>", {<Payload>}]
        */
        const char * format = "[%d, %Q, %Q, %s]\n";
        const char * Payload_key = "$[3]";
        const char * Action_key = "$[2]";

        string GenerateUniqueId() {
            static int i = 0;
            ++i;
            return to_string(i);
        }
};

class OCPP_Client;

class PendingCalls {
    private:
        vector<PendingCall *> call_list_;
        // map<string, string> call_map_;
    public:
        PendingCalls(OCPP_Client * client): client_(client) {}
        ~PendingCalls() = default;
        void StoreCall(PendingCall* call);
        bool GetCallActionWithId(string & id, string & action);
        void Update();
        OCPP_Client * client_;
};

