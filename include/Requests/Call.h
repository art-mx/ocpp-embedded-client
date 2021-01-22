#pragma once

#include <Arduino.h>
#include <vector>
#include <map>
#include <memory>
#include "Types/Types.h"
// #include "Requests/CallResult.h"
#include "Requests/Call.h"
#include "Requests/Message.h" 
using namespace std;

#define MAX_CALL_NUM 10 // number of calls to store

class Call : public Message {
    public:
        Call(string Action, string Payload);
        Call();
        ~Call() = default;
        const uint8_t MessageTypeId = MessageType::CALL;
        string Action;
        string UniqueId;
        string Payload;
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

class PendingCalls {
    private:
        vector<Call *> call_list_;
        // map<string, string> call_map_;
    public:
        PendingCalls() {}
        ~PendingCalls() = default;
        void StoreCall(Call* call);
        bool GetCallActionWithId(string & id, string & action);
        void Update();
};

