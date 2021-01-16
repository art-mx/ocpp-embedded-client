#include <Arduino.h>
#include <vector>
#pragma once

using namespace std;

#define MAX_CALL_NUM 10 // number of calls to store
#define BOOT_NOTIFICATION 1


class Call {
    public:
        Call(string Action, string Payload);
        // ~Call();
        const uint8_t MessageTypeId = 2;
        string Action;
        string UniqueId;
        string Payload;
        /*
        * [<MessageTypeId>, "<UniqueId>", "<Action>", {<Payload>}]
        */
        const char * call_format = "[%d, %Q, %Q, %Q]";
        string GenerateUniqueId() {return "12345";}
};

class PendingCalls {
    public:
        PendingCalls()  {} ;
        ~PendingCalls() = default;
        vector<Call*> call_list_;
        void StoreCall(Call * call);
        bool GetCallActionWithId(string & id, string & action);

};

